#pragma once
#include "Define.h"
#include "Device.h"

namespace Tempest{
	class SwapChain
	{
	public:
		void Init(const Device& i_device);
		void CleanUp();

		uint32_t width;
		uint32_t height;

	private:
		const Device* device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		const VkSwapchainKHR& Get() const { return swapchain; }
		const VkImage& GetImage(int index) const { return color_images[index]; }
		const VkImageView& GetImageView(int index) const { return color_image_views[index]; }
		const Array<VkImage>& GetImages() const { return color_images; }
		const Array<VkImageView>& GetImageViews() const { return color_image_views; }
		const VkImageView& GetDepthImageView() const { return depth_image_view; }
		VkFormat GetColorFormat() const { return color_format; }
		VkFormat GetDepthFormat() const { return depth_format; }

	private:
		VkSwapchainKHR swapchain;
		Array<VkImage> color_images;
		Array<VkImageView> color_image_views;
		VkFormat color_format;
		VkImage depth_image;
		VkImageView depth_image_view;
		VkDeviceMemory depth_image_memory;
		VkFormat depth_format;
#endif // ENGINE_GRAPHIC_VULKAN
	};
}
