#pragma once
#include "Define.h"
#include "Device.h"

namespace Tempest{
	class SwapChain
	{
	public:
		void Init(const Device& i_device);
		void CleanUp();

#ifdef ENGINE_GRAPHIC_VULKAN
		VkSwapchainKHR swapchain;
		Array<VkImage> swapchain_images;
		Array<VkImageView> swapchain_image_views;

		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities;
			Array<VkSurfaceFormatKHR> formats;
			Array<VkPresentModeKHR> present_modes;
			VkExtent2D extent;
			uint32_t image_count;
			uint32_t available_format_index;
			uint32_t available_present_mode_index;
		} support_details;

	private:
		const Device* device;
#endif // ENGINE_GRAPHIC_VULKAN
	};
}
