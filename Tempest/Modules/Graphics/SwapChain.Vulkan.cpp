#include "SwapChain.h"

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

		DEBUG_ASSERT(false);
		return 0;
	}
}

namespace Tempest
{
	void SwapChain::Init(const Device& i_device)
	{
		device = &i_device;

		struct SupportDetail
		{
			VkSurfaceCapabilitiesKHR capabilities;
			Array<VkSurfaceFormatKHR> formats;
			Array<VkPresentModeKHR> present_modes;
			VkExtent2D extent;
			uint32_t image_count;
			uint32_t available_format_index;
			uint32_t available_present_mode_index;
		}support_details = {};

		// Get infos related to swapchain
		{
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->physical_device, device->surface, &support_details.capabilities);

			uint32_t format_count;
			vkGetPhysicalDeviceSurfaceFormatsKHR(device->physical_device, device->surface, &format_count, nullptr);
			if (format_count != 0)
			{
				support_details.formats.Resize(format_count);
				vkGetPhysicalDeviceSurfaceFormatsKHR(device->physical_device, device->surface, &format_count, support_details.formats.Data());
			}

			uint32_t presetn_mode_count;
			vkGetPhysicalDeviceSurfacePresentModesKHR(device->physical_device, device->surface, &presetn_mode_count, nullptr);
			if (presetn_mode_count != 0)
			{
				support_details.present_modes.Resize(presetn_mode_count);
				vkGetPhysicalDeviceSurfacePresentModesKHR(device->physical_device, device->surface, &presetn_mode_count, support_details.present_modes.Data());
			}

			bool swapchain_adequate = false;
			swapchain_adequate = !support_details.formats.Empty() && !support_details.present_modes.Empty();
			DEBUG_ASSERT(swapchain_adequate);

			bool has_avaiable_surface_format = false;
			int available_format_index = 0;
			for (const auto& available_format : support_details.formats)
			{
				if (available_format.format == VK_FORMAT_B8G8R8A8_SRGB && available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				{
					has_avaiable_surface_format = true;
					support_details.available_format_index = available_format_index;
					break;
				}
				available_format_index++;
			}
			DEBUG_ASSERT(has_avaiable_surface_format);

			int available_present_mode_index = 0;
			VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;
			for (const auto& available_present_mode : support_details.present_modes)
			{
				if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR)
				{
					present_mode = VK_PRESENT_MODE_MAILBOX_KHR;
					support_details.available_present_mode_index = available_present_mode_index;
				}
				available_present_mode_index++;
			}


			support_details.extent.width = std::clamp(ScreenWidth, support_details.capabilities.minImageExtent.width, support_details.capabilities.maxImageExtent.width);
			support_details.extent.height = std::clamp(ScreenHeight, support_details.capabilities.minImageExtent.height, support_details.capabilities.maxImageExtent.height);

			support_details.image_count = support_details.capabilities.minImageCount + 1;

			if (support_details.capabilities.maxImageCount > 0 && support_details.image_count > support_details.capabilities.maxImageCount)
			{
				support_details.image_count = support_details.capabilities.maxImageCount;
			}
		}

		// Create Swapchain
		{
			VkSwapchainCreateInfoKHR create_swapchain_info{};
			create_swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			create_swapchain_info.surface = device->surface;
			create_swapchain_info.minImageCount = support_details.image_count;
			create_swapchain_info.imageFormat = support_details.formats[support_details.available_format_index].format;
			create_swapchain_info.imageColorSpace = support_details.formats[support_details.available_format_index].colorSpace;
			create_swapchain_info.imageExtent = support_details.extent;
			create_swapchain_info.imageArrayLayers = 1;
			create_swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

			uint32_t queue_family_indices[] = { device->queue_family_indices.graphics_family.value(), device->queue_family_indices.present_family.value() };

			if (device->queue_family_indices.graphics_family != device->queue_family_indices.present_family)
			{
				create_swapchain_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
				create_swapchain_info.queueFamilyIndexCount = 2;
				create_swapchain_info.pQueueFamilyIndices = queue_family_indices;
			}
			else
			{
				create_swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			}

			create_swapchain_info.preTransform = support_details.capabilities.currentTransform;
			create_swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			create_swapchain_info.presentMode = support_details.present_modes[support_details.available_present_mode_index];
			create_swapchain_info.clipped = VK_TRUE;
			create_swapchain_info.oldSwapchain = VK_NULL_HANDLE;

			VkResult create_swapchain_result = vkCreateSwapchainKHR(device->logical_device, &create_swapchain_info, nullptr, &swapchain);
			DEBUG_ASSERT(create_swapchain_result == VK_SUCCESS);

			uint32_t image_count;
			vkGetSwapchainImagesKHR(device->logical_device, swapchain, &image_count, nullptr);
			color_images.Resize(image_count);
			vkGetSwapchainImagesKHR(device->logical_device, swapchain, &image_count, color_images.Data());
		}

		// Create color image view
		color_image_views.Resize(color_images.Size());
		for (int i = 0; i < color_image_views.Size(); i++)
		{
			VkImageViewCreateInfo create_view_image_info = {};
			create_view_image_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			create_view_image_info.image = color_images[i];
			create_view_image_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
			create_view_image_info.format = support_details.formats[support_details.available_format_index].format;
			create_view_image_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			create_view_image_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			create_view_image_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			create_view_image_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			create_view_image_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			create_view_image_info.subresourceRange.baseMipLevel = 0;
			create_view_image_info.subresourceRange.levelCount = 1;
			create_view_image_info.subresourceRange.baseArrayLayer = 0;
			create_view_image_info.subresourceRange.layerCount = 1;

			VkResult create_image_result = vkCreateImageView(device->logical_device, &create_view_image_info, nullptr, &color_image_views[i]);
			DEBUG_ASSERT(create_image_result == VK_SUCCESS);
		}

		width = support_details.extent.width;
		height = support_details.extent.height;
		color_format = support_details.formats[support_details.available_format_index].format;
		depth_format = VK_FORMAT_D32_SFLOAT;

		{
			VkImageCreateInfo image_info{};
			image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			image_info.imageType = VK_IMAGE_TYPE_2D;
			image_info.extent.width = width;
			image_info.extent.height = height;
			image_info.extent.depth = 1;
			image_info.mipLevels = 1;
			image_info.arrayLayers = 1;
			image_info.format = depth_format;
			image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
			image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
			image_info.samples = VK_SAMPLE_COUNT_1_BIT;
			image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			auto image_create_result = vkCreateImage(device->logical_device, &image_info, nullptr, &depth_image);
			DEBUG_ASSERT(image_create_result == VK_SUCCESS)

			VkMemoryRequirements memory_requirements;
			vkGetImageMemoryRequirements(device->logical_device, depth_image, &memory_requirements);

			VkMemoryAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memory_requirements.size;
			allocInfo.memoryTypeIndex = FindMemoryType(device->physical_device, memory_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			auto allocate_result = vkAllocateMemory(device->logical_device, &allocInfo, nullptr, &depth_image_memory);
			DEBUG_ASSERT(allocate_result == VK_SUCCESS)
			vkBindImageMemory(device->logical_device, depth_image, depth_image_memory, 0);

			VkImageViewCreateInfo view_info{};
			view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			view_info.image = depth_image;
			view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
			view_info.format = depth_format;
			view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
			view_info.subresourceRange.baseMipLevel = 0;
			view_info.subresourceRange.levelCount = 1;
			view_info.subresourceRange.baseArrayLayer = 0;
			view_info.subresourceRange.layerCount = 1;

			auto view_create_result = vkCreateImageView(device->logical_device, &view_info, nullptr, &depth_image_view);
			DEBUG_ASSERT(view_create_result == VK_SUCCESS)
		}
	}

	void SwapChain::CleanUp()
	{
		for (auto image_view : color_image_views)
		{
			vkDestroyImageView(device->logical_device, image_view, nullptr);
		}

		vkDestroyImage(device->logical_device, depth_image, nullptr);
		vkDestroyImageView(device->logical_device, depth_image_view, nullptr);

		vkDestroySwapchainKHR(device->logical_device, swapchain, nullptr);
	}
}
#endif