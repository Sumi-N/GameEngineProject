#include "UniformBuffer.h"

#ifdef  ENGINE_GRAPHIC_VULKAN
namespace
{
	uint32_t FindMemoryType(VkPhysicalDevice physical_device, uint32_t type_filter, VkMemoryPropertyFlags properties)
	{

		VkPhysicalDeviceMemoryProperties memory_properties;
		vkGetPhysicalDeviceMemoryProperties(physical_device, &memory_properties);

		for (uint32_t i = 0; i < memory_properties.memoryTypeCount; i++)
		{
			if ((type_filter & (1 << i)) && (memory_properties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				return i;
			}
		}

		DEBUG_ASSERT(false);
		return 0;
	}

	void CreateBuffer(VkPhysicalDevice physical_device, VkDevice logical_device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory)
	{
		VkBufferCreateInfo buffer_info{};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = size;
		buffer_info.usage = usage;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		auto create_result = vkCreateBuffer(logical_device, &buffer_info, nullptr, &buffer);
		DEBUG_ASSERT(create_result == VK_SUCCESS);

		VkMemoryRequirements memory_requirements;
		vkGetBufferMemoryRequirements(logical_device, buffer, &memory_requirements);

		VkMemoryAllocateInfo alloc_info{};
		alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_info.allocationSize = memory_requirements.size;
		alloc_info.memoryTypeIndex = FindMemoryType(physical_device, memory_requirements.memoryTypeBits, properties);

		auto allocate_result = vkAllocateMemory(logical_device, &alloc_info, nullptr, &buffer_memory);
		DEBUG_ASSERT(allocate_result == VK_SUCCESS);

		vkBindBufferMemory(logical_device, buffer, buffer_memory, 0);
	}
}

namespace Tempest
{
	void UniformBuffer::Init(const Device& i_device, const Shader& i_shader)
	{
		device = &i_device;

		// Create uniform buffer
		{
			VkDeviceSize buffer_size = 0;
			for (int i = 0; i < static_cast<int>(ShaderType::Size); i++)
			{
				if (i_shader.uniform_infos[i].Size() == 0)
					continue;
				for (int j = 0; j < i_shader.uniform_infos[i].Size(); j++)
				{
					buffer_size += i_shader.uniform_infos[i][j].size;
				}
			}

			for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			{
				CreateBuffer(device->physical_device,
							 device->logical_device,
							 buffer_size,
							 VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
							 uniformbuffers[i],
							 uniformbuffers_memory[i]);
			}
		}

		// Create descriptor layout
		{
			Array<VkDescriptorSetLayoutBinding> ubo_layout_bindings{};
			for (int i = 0; i < static_cast<int>(ShaderType::Size); i++)
			{
				if (i_shader.uniform_infos[i].Size() == 0)
					continue;
				for (int j = 0; j < i_shader.uniform_infos[i].Size(); j++)
				{
					VkDescriptorSetLayoutBinding ubo_layout_binding;
					ubo_layout_binding.binding = i_shader.uniform_infos[i][j].binding;
					ubo_layout_binding.descriptorCount = 1;
					ubo_layout_binding.descriptorType = static_cast<VkDescriptorType>(i_shader.uniform_infos[i][j].type);
					ubo_layout_binding.stageFlags = static_cast<VkShaderStageFlagBits>(i_shader.uniform_infos[i][j].stage);
					ubo_layout_binding.pImmutableSamplers = nullptr;

					ubo_layout_bindings.PushBack(ubo_layout_binding);
				}
			}

			VkDescriptorSetLayoutCreateInfo layout_info{};
			layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			layout_info.bindingCount = static_cast<uint32_t>(ubo_layout_bindings.Size());
			layout_info.pBindings = ubo_layout_bindings.Data();
			auto descriptorset_layout_create_result = vkCreateDescriptorSetLayout(device->logical_device, &layout_info, nullptr, &descriptorset_layout);
			DEBUG_ASSERT(descriptorset_layout_create_result == VK_SUCCESS);
		}

		// Create descriptor pool
		{
			VkDescriptorPoolSize pool_size{};
			pool_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			pool_size.descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

			VkDescriptorPoolCreateInfo pool_info{};
			pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			pool_info.poolSizeCount = 1;
			pool_info.pPoolSizes = &pool_size;
			pool_info.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

			if (vkCreateDescriptorPool(device->logical_device, &pool_info, nullptr, &descriptor_pool) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create descriptor pool!");
			}
		}

		{
			VkDescriptorSetLayout layouts[MAX_FRAMES_IN_FLIGHT];
			for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			{
				layouts[i] = descriptorset_layout;
			}
			VkDescriptorSetAllocateInfo alloc_info{};
			alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			alloc_info.descriptorPool = descriptor_pool;
			alloc_info.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
			alloc_info.pSetLayouts = layouts;

			auto alloc_info_result = vkAllocateDescriptorSets(device->logical_device, &alloc_info, descriptor_sets);
			DEBUG_ASSERT(alloc_info_result == VK_SUCCESS);

			for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			{
				VkDescriptorBufferInfo buffer_info{};
				buffer_info.buffer = uniformbuffers[i];
				buffer_info.offset = 0;
				buffer_info.range = VK_WHOLE_SIZE;

				VkWriteDescriptorSet descriptor_write{};
				descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				descriptor_write.dstSet = descriptor_sets[i];
				descriptor_write.dstBinding = 0;
				descriptor_write.dstArrayElement = 0;
				descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				descriptor_write.descriptorCount = 1;
				descriptor_write.pBufferInfo = &buffer_info;

				vkUpdateDescriptorSets(device->logical_device, 1, &descriptor_write, 0, nullptr);
			}
		}
	}

	void UniformBuffer::CleanUp()
	{
		for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			vkDestroyBuffer(device->logical_device, uniformbuffers[i], nullptr);
			vkFreeMemory(device->logical_device, uniformbuffers_memory[i], nullptr);
		}
		vkDestroyDescriptorPool(device->logical_device, descriptor_pool, nullptr);
		vkDestroyDescriptorSetLayout(device->logical_device, descriptorset_layout, nullptr);
	}

	void UniformBuffer::Update(int i_index, void* i_uniform_data, size_t i_uniform_size)
	{
		void* data;
		vkMapMemory(device->logical_device, uniformbuffers_memory[i_index], 0, i_uniform_size, 0, &data);
		memcpy(data, i_uniform_data, i_uniform_size);
		vkUnmapMemory(device->logical_device, uniformbuffers_memory[i_index]);
	}
}
#endif // ENGINE_GRAPHIC_OPENGL