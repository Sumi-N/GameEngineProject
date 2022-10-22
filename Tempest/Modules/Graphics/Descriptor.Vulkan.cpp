#include "Descriptor.h"

#ifdef  ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	VkDescriptorType GetDescriptorType(ShaderDescriptorType i_type)
	{
		switch (i_type)
		{
		case ShaderDescriptorType::Sampler:              return VK_DESCRIPTOR_TYPE_SAMPLER;
		case ShaderDescriptorType::CombinedImageSampler: return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		case ShaderDescriptorType::SapmledImage:         return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
		case ShaderDescriptorType::StorageImage:         return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
		case ShaderDescriptorType::UniformTexelBuffer:   return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
		case ShaderDescriptorType::StorageTexelBuffer:   return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
		case ShaderDescriptorType::UniformBuffer:        return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		case ShaderDescriptorType::StorageBuffer:        return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		default:
			break;
		}
		DEBUG_ASSERT(false);
		return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	}

	void Descriptor::Init(const Device& i_device, const Shader& i_shader)
	{
		device = &i_device;

		uint32_t descriptor_type_counts[static_cast<int>(ShaderDescriptorType::Size)] = {};

		// Create attribute descriptor
		{
			attribute_descriptions.Resize(i_shader.vertex_info.Size());
			for (int i = 0; i < attribute_descriptions.Size(); i++)
			{
				attribute_descriptions[i].binding = i_shader.vertex_info[i].binding;
				attribute_descriptions[i].location = i_shader.vertex_info[i].location;
				attribute_descriptions[i].format = static_cast<VkFormat>(i_shader.vertex_info[i].format);
				attribute_descriptions[i].offset = i_shader.vertex_info[i].offset;
			}
		}

		// Create descriptor layout
		{
			Array<VkDescriptorSetLayoutBinding> layout_bindings{};
			for (int i = 0; i < static_cast<int>(ShaderType::Size); i++)
			{
				if (i_shader.uniform_infos[i].Size() == 0)
					continue;
				for (int j = 0; j < i_shader.uniform_infos[i].Size(); j++)
				{
					VkDescriptorSetLayoutBinding layout_binding;
					layout_binding.binding = i_shader.uniform_infos[i][j].binding;
					layout_binding.descriptorCount = 1;
					layout_binding.descriptorType = GetDescriptorType(i_shader.uniform_infos[i][j].type);
					layout_binding.stageFlags = static_cast<VkShaderStageFlagBits>(i_shader.uniform_infos[i][j].stage);
					layout_binding.pImmutableSamplers = nullptr;

					layout_bindings.PushBack(layout_binding);

					descriptor_type_counts[static_cast<int>(i_shader.uniform_infos[i][j].type)]++;
				}
			}

			VkDescriptorSetLayoutCreateInfo layout_info{};
			layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			layout_info.bindingCount = static_cast<uint32_t>(layout_bindings.Size());
			layout_info.pBindings = layout_bindings.Data();
			auto descriptorset_layout_create_result = vkCreateDescriptorSetLayout(device->logical_device, &layout_info, nullptr, &descriptorset_layout);
			DEBUG_ASSERT(descriptorset_layout_create_result == VK_SUCCESS)
		}

		// Create descriptor pool
		{
			VkDescriptorPoolSize pool_sizes[static_cast<int>(ShaderDescriptorType::Size)];
			int descriptor_index_count = 0;
			for (int i = 0; i < static_cast<int>(ShaderDescriptorType::Size); i++)
			{
				if (descriptor_type_counts[i] == 0)
				{
					continue;
				}
				pool_sizes[descriptor_index_count].type = GetDescriptorType(static_cast<ShaderDescriptorType>(i));
				pool_sizes[descriptor_index_count].descriptorCount = descriptor_type_counts[i];
				descriptor_index_count++;
			}

			VkDescriptorPoolCreateInfo pool_info{};
			pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			pool_info.poolSizeCount = descriptor_index_count;
			pool_info.pPoolSizes = pool_sizes;
			pool_info.maxSets = Graphics::BufferingCount;

			auto descriptor_pool_create_result = vkCreateDescriptorPool(device->logical_device, &pool_info, nullptr, &descriptor_pool);
			DEBUG_ASSERT(descriptor_pool_create_result == VK_SUCCESS)
		}

		// Create descriptor set
		{
			VkDescriptorSetLayout layouts[Graphics::BufferingCount];
			for (int i = 0; i < Graphics::BufferingCount; i++)
			{
				layouts[i] = descriptorset_layout;
			}
			VkDescriptorSetAllocateInfo alloc_info{};
			alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			alloc_info.descriptorPool = descriptor_pool;
			alloc_info.descriptorSetCount = Graphics::BufferingCount;
			alloc_info.pSetLayouts = layouts;

			auto alloc_info_result = vkAllocateDescriptorSets(device->logical_device, &alloc_info, descriptor_sets);
			DEBUG_ASSERT(alloc_info_result == VK_SUCCESS)
		}
	}

	void Descriptor::CleanUp()
	{
		vkDestroyDescriptorPool(device->logical_device, descriptor_pool, nullptr);
		vkDestroyDescriptorSetLayout(device->logical_device, descriptorset_layout, nullptr);
	}

	void Descriptor::Bind(const VertexBuffer& i_vertex)
	{
		vertex_stride = i_vertex.layout.stride;
	}

	void Descriptor::Bind(const UniformBuffer& i_uniform, uint32_t i_binding)
	{
		for (int idx_count = 0; idx_count < Graphics::BufferingCount; idx_count++)
		{
			const BufferLayout& layout = i_uniform.layout;

			VkDescriptorBufferInfo descriptor_buffer_info{};
			descriptor_buffer_info.buffer = i_uniform.uniformbuffers[idx_count];
			descriptor_buffer_info.offset = 0;
			descriptor_buffer_info.range = layout.stride;

			VkWriteDescriptorSet descriptor_write{};
			descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptor_write.dstSet = descriptor_sets[idx_count];
			descriptor_write.dstBinding = i_binding;
			descriptor_write.dstArrayElement = 0;
			descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptor_write.descriptorCount = 1;
			descriptor_write.pBufferInfo = &descriptor_buffer_info;

			vkUpdateDescriptorSets(device->logical_device, 1, &descriptor_write, 0, nullptr);
		}
	}

	void Descriptor::Bind(const Texture& i_texture, uint32_t i_binding)
	{
		for (int idx_count = 0; idx_count < Graphics::BufferingCount; idx_count++)
		{
			VkDescriptorImageInfo descriptor_image_info{};
			descriptor_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			descriptor_image_info.imageView = i_texture.image_view;
			descriptor_image_info.sampler = i_texture.sampler;

			VkWriteDescriptorSet descriptor_write{};
			descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptor_write.dstSet = descriptor_sets[idx_count];
			descriptor_write.dstBinding = i_binding;
			descriptor_write.dstArrayElement = 0;
			descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptor_write.descriptorCount = 1;
			descriptor_write.pImageInfo = &descriptor_image_info;
			vkUpdateDescriptorSets(device->logical_device, 1, &descriptor_write, 0, nullptr);
		}
	}
}
#endif // ENGINE_GRAPHIC_VULKAN