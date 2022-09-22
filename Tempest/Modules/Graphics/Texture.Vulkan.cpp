#include "Texture.h"

#ifdef ENGINE_GRAPHIC_VULKAN
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

	void TransitionImageLayout(VkImage image, VkImageLayout old_layout, VkImageLayout new_layout, VkCommandBuffer commandbuffer)
	{
		VkImageMemoryBarrier barrier{};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout = old_layout;
		barrier.newLayout = new_layout;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image = image;
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;

		VkPipelineStageFlags sourceStage;
		VkPipelineStageFlags destinationStage;

		if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else
		{
			DEBUG_ASSERT(false);
		}

		vkCmdPipelineBarrier(
			commandbuffer,
			sourceStage, destinationStage,
			0,
			0, nullptr,
			0, nullptr,
			1, &barrier
		);
	}
}

namespace Tempest
{
	static VkFormat GetFormat(TextureFormat i_format)
	{
		switch (i_format)
		{
		case TextureFormat::R8G8A8_SRGB:           return VK_FORMAT_R8G8B8_SRGB;
		case TextureFormat::R8G8B8A8_SRGB:         return VK_FORMAT_R8G8B8A8_SRGB;
		case TextureFormat::R16G16_SFLOAT:         return VK_FORMAT_R16G16_SFLOAT;
		case TextureFormat::R32G32B32_SFLOAT:      return VK_FORMAT_R16G16B16_SFLOAT;
		/*case TextureFormat::D32_SFLOAT:            return VK_FORMAT_D32_SFLOAT;
		case TextureFormat::D32_SFLOAT_S8_UINT:    return VK_FORMAT_D32_SFLOAT_S8_UINT;
		case TextureFormat::D24_UNORM_S8_UINT:     return VK_FORMAT_D24_UNORM_S8_UINT;*/
		default:                                   DEBUG_ASSERT(false); break;
		}

		DEBUG_ASSERT(false);
		return VK_FORMAT_R8G8B8A8_SRGB;
	}

	static VkImageAspectFlags GetAspect(TextureInfoFlags i_aspect)
	{
		return static_cast<VkImageAspectFlags>(i_aspect);
	}

	static VkImageUsageFlags GetUsage(TextureInfoFlags i_usage)
	{
		return static_cast<VkImageUsageFlags>(i_usage);
	}

	void Texture::Init(const Device& i_device, const CommandBuffer& i_commandbuffer, const TextureInfo& i_textuer_info)
	{
		device = &i_device;
		const TextureInfo& info = i_textuer_info;
		image_size = info.width * info.height * static_cast<uint32_t>(info.format);
		width = info.width;
		height = info.height;

		VkBuffer stagingbuffer {};
		VkDeviceMemory stagingbuffer_memory {};

		if (info.has_data)
		{
			CreateBuffer(device->physical_device,
						 device->logical_device,
						 image_size,
						 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
						 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
						 stagingbuffer,
						 stagingbuffer_memory);

			void* mapped_data;
			vkMapMemory(device->logical_device, stagingbuffer_memory, 0, image_size, 0, &mapped_data);
			memcpy(mapped_data, info.pixels.Data(), image_size);
			vkUnmapMemory(device->logical_device, stagingbuffer_memory);
		}

		{
			VkImageCreateInfo image_info{};
			image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			image_info.imageType = VK_IMAGE_TYPE_2D;
			image_info.extent.width = static_cast<uint32_t>(info.width);
			image_info.extent.height = static_cast<uint32_t>(info.width);
			image_info.extent.depth = 1;
			image_info.mipLevels = 1;
			image_info.arrayLayers = 1;
			image_info.format = GetFormat(info.format);
			image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
			image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			image_info.usage = GetUsage(info.usage_flag);
			image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			image_info.samples = VK_SAMPLE_COUNT_1_BIT;
			image_info.flags = 0;

			auto image_create_result = vkCreateImage(device->logical_device, &image_info, nullptr, &texture_image);
			DEBUG_ASSERT(image_create_result == VK_SUCCESS);

			VkMemoryRequirements memory_requirements;
			vkGetImageMemoryRequirements(device->logical_device, texture_image, &memory_requirements);

			VkMemoryAllocateInfo alloc_info{};
			alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			alloc_info.allocationSize = memory_requirements.size;
			alloc_info.memoryTypeIndex = FindMemoryType(device->physical_device, memory_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			auto alloc_info_result = vkAllocateMemory(device->logical_device, &alloc_info, nullptr, &texture_image_memory);
			DEBUG_ASSERT(alloc_info_result == VK_SUCCESS);
			vkBindImageMemory(device->logical_device, texture_image, texture_image_memory, 0);
		}

		if (info.has_data)
		{
			auto vk_commandbuffer = i_commandbuffer.GetBuffer(0);
			VkCommandBufferBeginInfo begin_info{};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

			vkBeginCommandBuffer(vk_commandbuffer, &begin_info);

			TransitionImageLayout(texture_image,
								  VK_IMAGE_LAYOUT_UNDEFINED,
								  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
								  vk_commandbuffer);

			{
				VkBufferImageCopy region{};
				region.bufferOffset = 0;
				region.bufferRowLength = 0;
				region.bufferImageHeight = 0;
				region.imageSubresource.aspectMask = GetAspect(info.aspect_flag);
				region.imageSubresource.mipLevel = 0;
				region.imageSubresource.baseArrayLayer = 0;
				region.imageSubresource.layerCount = 1;
				region.imageOffset = { 0, 0, 0 };
				region.imageExtent = { static_cast<uint32_t>(info.width), static_cast<uint32_t>(info.height), 1 };

				vkCmdCopyBufferToImage(vk_commandbuffer, stagingbuffer, texture_image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
			}

			TransitionImageLayout(texture_image,
								  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
								  VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
								  vk_commandbuffer);

			vkEndCommandBuffer(vk_commandbuffer);

			VkSubmitInfo submit_info{};
			submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submit_info.commandBufferCount = 1;
			submit_info.pCommandBuffers = &vk_commandbuffer;

			VkQueue graphics_queue;
			vkGetDeviceQueue(device->logical_device, device->queue_family_indices.graphics_family.value(), 0, &graphics_queue);
			vkQueueSubmit(graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
			vkQueueWaitIdle(graphics_queue);
		}

		// Create texture view
		{
			VkImageViewCreateInfo view_info{};
			view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			view_info.image = texture_image;
			view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
			view_info.format = GetFormat(info.format);;
			view_info.subresourceRange.aspectMask = GetAspect(info.aspect_flag);
			view_info.subresourceRange.baseMipLevel = 0;
			view_info.subresourceRange.levelCount = 1;
			view_info.subresourceRange.baseArrayLayer = 0;
			view_info.subresourceRange.layerCount = 1;

			auto image_view_create_result = vkCreateImageView(device->logical_device, &view_info, nullptr, &texture_image_view);
			DEBUG_ASSERT(image_view_create_result == VK_SUCCESS);
		}

		// Create sampler
		if(info.sampler_needed)
		{
			VkSamplerCreateInfo sampler_info{};
			sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			sampler_info.magFilter = VK_FILTER_LINEAR;
			sampler_info.minFilter = VK_FILTER_LINEAR;
			sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			sampler_info.anisotropyEnable = VK_TRUE;
			sampler_info.maxAnisotropy = device->max_sampler_anisotropy;
			sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			sampler_info.unnormalizedCoordinates = VK_FALSE;
			sampler_info.compareEnable = VK_FALSE;
			sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
			sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

			auto sampler_create_result = vkCreateSampler(device->logical_device, &sampler_info, nullptr, &texture_sampler);
			DEBUG_ASSERT(sampler_create_result == VK_SUCCESS);
		}
	}

	void Texture::CleanUp()
	{
		vkDestroySampler(device->logical_device, texture_sampler, nullptr);
		vkDestroyImageView(device->logical_device, texture_image_view, nullptr);
		vkDestroyImage(device->logical_device, texture_image, nullptr);
		vkFreeMemory(device->logical_device, texture_image_memory, nullptr);
	}
}
#endif