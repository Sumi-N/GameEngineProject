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

		DEBUG_ASSERT(false)
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
		DEBUG_ASSERT(create_result == VK_SUCCESS)

		VkMemoryRequirements memory_requirements;
		vkGetBufferMemoryRequirements(logical_device, buffer, &memory_requirements);

		VkMemoryAllocateInfo alloc_info{};
		alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_info.allocationSize = memory_requirements.size;
		alloc_info.memoryTypeIndex = FindMemoryType(physical_device, memory_requirements.memoryTypeBits, properties);

		auto allocate_result = vkAllocateMemory(logical_device, &alloc_info, nullptr, &buffer_memory);
		DEBUG_ASSERT(allocate_result == VK_SUCCESS)

		vkBindBufferMemory(logical_device, buffer, buffer_memory, 0);
	}
}

namespace Tempest
{
	void UniformBuffer::Init(const Device& i_device, const Shader& i_shader, const Texture& i_texture)
	{
		device = &i_device;
		buffer_count = device->graphics_buffering_count;
		buffer_offset_alignment = device->min_uniform_buffer_offset_alignment;

		// Create uniform buffer
		{
			VkDeviceSize buffer_size = 0;
			for (int i = 0; i < static_cast<int>(ShaderType::Size); i++)
			{
				if (i_shader.uniform_infos[i].Size() == 0)
					continue;
				for (int j = 0; j < i_shader.uniform_infos[i].Size(); j++)
				{
					// Need to fix this later.
					DEBUG_ASSERT(i_shader.uniform_infos[i][j].size <= buffer_offset_alignment)
					buffer_size += buffer_offset_alignment;
				}
			}

			uniformbuffers.Resize(buffer_count);
			uniformbuffers_memories.Resize(buffer_count);
			for (size_t i = 0; i < buffer_count; i++)
			{
				CreateBuffer(device->physical_device,
							 device->logical_device,
							 buffer_size,
							 VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
							 uniformbuffers[i],
							 uniformbuffers_memories[i]);
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
			DEBUG_ASSERT(descriptorset_layout_create_result == VK_SUCCESS)
		}

		// Create descriptor pool
		{
			Array<VkDescriptorPoolSize> pool_size(2);
			pool_size[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			pool_size[0].descriptorCount = buffer_count;
			pool_size[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			pool_size[1].descriptorCount = buffer_count;

			VkDescriptorPoolCreateInfo pool_info{};
			pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			pool_info.poolSizeCount = pool_size.Size();
			pool_info.pPoolSizes = pool_size.Data();
			pool_info.maxSets = buffer_count;

			auto descriptor_pool_create_result = vkCreateDescriptorPool(device->logical_device, &pool_info, nullptr, &descriptor_pool);
			DEBUG_ASSERT(descriptor_pool_create_result == VK_SUCCESS)
		}

		// Create descriptor set
		{
			Array<VkDescriptorSetLayout> layouts;
			layouts.Resize(buffer_count);
			for (int i = 0; i < buffer_count; i++)
			{
				layouts[i] = descriptorset_layout;
			}
			VkDescriptorSetAllocateInfo alloc_info{};
			alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			alloc_info.descriptorPool = descriptor_pool;
			alloc_info.descriptorSetCount = buffer_count;
			alloc_info.pSetLayouts = layouts.Data();

			descriptor_sets.Resize(buffer_count);
			auto alloc_info_result = vkAllocateDescriptorSets(device->logical_device, &alloc_info, descriptor_sets.Data());
			DEBUG_ASSERT(alloc_info_result == VK_SUCCESS)

			for (size_t i = 0; i < buffer_count; i++)
			{
				size_t buffer_offset = 0;
				for (int j = 0; j < static_cast<int>(ShaderType::Size); j++)
				{
					if (i_shader.uniform_infos[j].Size() == 0)
						continue;
					for (int k = 0; k < i_shader.uniform_infos[j].Size(); k++)
					{
						if (static_cast<VkDescriptorType>(i_shader.uniform_infos[j][k].type) == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
						{
							VkDescriptorBufferInfo buffer_info{};
							buffer_info.buffer = uniformbuffers[i];
							buffer_info.offset = buffer_offset;
							buffer_info.range = i_shader.uniform_infos[j][k].size;

							VkWriteDescriptorSet descriptor_write{};
							descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
							descriptor_write.dstSet = descriptor_sets[i];
							descriptor_write.dstBinding = i_shader.uniform_infos[j][k].binding;
							descriptor_write.dstArrayElement = 0;
							descriptor_write.descriptorType = static_cast<VkDescriptorType>(i_shader.uniform_infos[j][k].type);
							descriptor_write.descriptorCount = 1;
							descriptor_write.pBufferInfo = &buffer_info;

							vkUpdateDescriptorSets(device->logical_device, 1, &descriptor_write, 0, nullptr);
							buffer_offset += buffer_offset_alignment;
						}
						else if (static_cast<VkDescriptorType>(i_shader.uniform_infos[j][k].type) == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
						{
							VkDescriptorImageInfo image_info{};
							image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
							image_info.imageView =  i_texture.GetImageView();
							image_info.sampler = i_texture.GetImageSampler();

							VkWriteDescriptorSet descriptor_write{};
							descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
							descriptor_write.dstSet = descriptor_sets[i];
							descriptor_write.dstBinding = i_shader.uniform_infos[j][k].binding;
							descriptor_write.dstArrayElement = 0;
							descriptor_write.descriptorType = static_cast<VkDescriptorType>(i_shader.uniform_infos[j][k].type);
							descriptor_write.descriptorCount = 1;
							descriptor_write.pImageInfo = &image_info;
							vkUpdateDescriptorSets(device->logical_device, 1, &descriptor_write, 0, nullptr);
						}
					}
				}
			}
		}
	}

	void UniformBuffer::CleanUp()
	{
		for (int i = 0; i < buffer_count; i++)
		{
			vkDestroyBuffer(device->logical_device, uniformbuffers[i], nullptr);
			vkFreeMemory(device->logical_device, uniformbuffers_memories[i], nullptr);
		}
		vkDestroyDescriptorPool(device->logical_device, descriptor_pool, nullptr);
		vkDestroyDescriptorSetLayout(device->logical_device, descriptorset_layout, nullptr);
	}

	void UniformBuffer::Update(int i_index, void* i_data, size_t i_size, size_t i_offset) const
	{
		void* memory_data;
		vkMapMemory(device->logical_device, uniformbuffers_memories[i_index], i_offset, i_size, 0, &memory_data);
		memcpy(memory_data, i_data, i_size);
		vkUnmapMemory(device->logical_device, uniformbuffers_memories[i_index]);
	}
}
#endif // ENGINE_GRAPHIC_OPENGL