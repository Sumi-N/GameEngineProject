#pragma once
#include "Define.h"
#include "Device.h"

namespace Tempest{
	class SwapChain
	{
	public:
		void Init(const Device& i_device);
		void CleanUp();

		const VkSwapchainKHR&     Get() const { return swapchain; }
		const VkImage&            GetImage(int index) const { return swapchain_images[index]; }
		const VkImageView&        GetImageView(int index) const { return swapchain_image_views[index]; }
		const Array<VkImage>&     GetImages() const { return swapchain_images; }
		const Array<VkImageView>& GetImageViews() const { return swapchain_image_views; }

#ifdef ENGINE_GRAPHIC_VULKAN
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
		VkSwapchainKHR swapchain;
		Array<VkImage> swapchain_images;
		Array<VkImageView> swapchain_image_views;
#endif // ENGINE_GRAPHIC_VULKAN
	};
}
