#include "SwapChain.h"

#ifdef ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	void SwapChain::Init(const Device& i_device)
	{
		device = &i_device;

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

			uint32_t queueFamilyIndices[] = { device->queue_family_indices.graphics_family.value(), device->queue_family_indices.present_family.value() };

			if (device->queue_family_indices.graphics_family != device->queue_family_indices.present_family)
			{
				create_swapchain_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
				create_swapchain_info.queueFamilyIndexCount = 2;
				create_swapchain_info.pQueueFamilyIndices = queueFamilyIndices;
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
			swapchain_images.Resize(image_count);
			vkGetSwapchainImagesKHR(device->logical_device, swapchain, &image_count, swapchain_images.Data());
		}

		swapchain_image_views.Resize(swapchain_images.Size());
		for (int i = 0; i < swapchain_image_views.Size(); i++)
		{
			VkImageViewCreateInfo create_view_image_info = {};
			create_view_image_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			create_view_image_info.image = swapchain_images[i];
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

			VkResult create_image_result = vkCreateImageView(device->logical_device, &create_view_image_info, nullptr, &swapchain_image_views[i]);
			DEBUG_ASSERT(create_image_result == VK_SUCCESS);
		}
	}

	void SwapChain::CleanUp()
	{
		for (auto image_view : swapchain_image_views)
		{
			vkDestroyImageView(device->logical_device, image_view, nullptr);
		}

		vkDestroySwapchainKHR(device->logical_device, swapchain, nullptr);
	}
}
#endif