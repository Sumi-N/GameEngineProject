#include "FrameBuffer.h"

#ifdef ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	void FrameBuffer::Init(const Device& i_device, const RenderPass& i_render_pass, const SwapChain& i_swapchain, uint32_t index)
	{
		device = &i_device;
		render_pass = &i_render_pass;
		width = i_swapchain.width;
		height = i_swapchain.height;

		VkImageView image_views[] = {i_swapchain.GetImageView(index), i_swapchain.GetDepthImageView() };
		VkFramebufferCreateInfo framebuffer_create_info{};
		framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebuffer_create_info.renderPass = render_pass->renderpass;
		framebuffer_create_info.attachmentCount = 2;
		framebuffer_create_info.pAttachments = image_views;
		framebuffer_create_info.width = i_swapchain.width;
		framebuffer_create_info.height = i_swapchain.height;
		framebuffer_create_info.layers = 1;

		const VkResult& result = vkCreateFramebuffer(device->logical_device, &framebuffer_create_info, nullptr, &framebuffer);
		DEBUG_ASSERT(result == VK_SUCCESS);
	}

	void FrameBuffer::Init(const Device& i_device, const RenderPass& i_render_pass, const Texture& i_texture, uint32_t i_miplevel)
	{
		device = &i_device;
		render_pass = &i_render_pass;
		width = i_texture.width >> i_miplevel;
		height = i_texture.height >> i_miplevel;

		VkFramebufferCreateInfo framebuffer_create_info{};
		framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebuffer_create_info.renderPass = i_render_pass.renderpass;
		framebuffer_create_info.attachmentCount = 1;
		framebuffer_create_info.pAttachments = &i_texture.image_views[i_miplevel];
		framebuffer_create_info.width = width;
		framebuffer_create_info.height = height;
		framebuffer_create_info.layers = i_texture.count;

		const VkResult& result = vkCreateFramebuffer(device->logical_device, &framebuffer_create_info, nullptr, &framebuffer);
		DEBUG_ASSERT(result == VK_SUCCESS);
	}

	void FrameBuffer::CleanUp() const
	{
		vkDestroyFramebuffer(device->logical_device, framebuffer, nullptr);
	}
}
#endif // ENGINE_GRAPHIC_VULKAN