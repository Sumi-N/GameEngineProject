#include "FrameBuffer.h"

#ifdef ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	void FrameBuffer::Init(const Device& i_device, const RenderPass& i_render_pass, const SwapChain& i_swapchain, int index)
	{
		device = &i_device;
		render_pass = &i_render_pass;
		width = i_swapchain.width;
		height = i_swapchain.height;

		VkImageView image_views[] = {i_swapchain.GetImageView(index), i_swapchain.GetDepthImageView() };
		VkFramebufferCreateInfo framebuffer_create_info{};
		framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebuffer_create_info.renderPass = render_pass->GetRenderPass();
		framebuffer_create_info.attachmentCount = 2;
		framebuffer_create_info.pAttachments = image_views;
		framebuffer_create_info.width = i_swapchain.width;
		framebuffer_create_info.height = i_swapchain.height;
		framebuffer_create_info.layers = 1;

		const VkResult& result = vkCreateFramebuffer(device->logical_device, &framebuffer_create_info, nullptr, &framebuffer);
		DEBUG_ASSERT(result == VK_SUCCESS);
	}

	void FrameBuffer::Init(const Device& i_device, const RenderPass& i_render_pass, const Texture& i_texture)
	{
		device = &i_device;
		render_pass = &i_render_pass;
		width = i_texture.width;
		height = i_texture.height;

		VkFramebufferCreateInfo framebuffer_create_info{};
		framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebuffer_create_info.renderPass = i_render_pass.GetRenderPass();
		framebuffer_create_info.attachmentCount = 1;
		framebuffer_create_info.pAttachments = &i_texture.GetImageView();
		framebuffer_create_info.width = width;
		framebuffer_create_info.height = height;
		framebuffer_create_info.layers = 1;

		const VkResult& result = vkCreateFramebuffer(device->logical_device, &framebuffer_create_info, nullptr, &framebuffer);
		DEBUG_ASSERT(result == VK_SUCCESS);
	}

	void FrameBuffer::CleanUp() const
	{
		vkDestroyFramebuffer(device->logical_device, framebuffer, nullptr);
	}

	VkRenderPassBeginInfo FrameBuffer::GetBeginInfo() const
	{
		VkRenderPassBeginInfo renderpass_begin_info{};
		renderpass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderpass_begin_info.renderPass = render_pass->GetRenderPass();
		renderpass_begin_info.framebuffer = framebuffer;
		renderpass_begin_info.renderArea.offset = { 0, 0 };
		renderpass_begin_info.renderArea.extent = { width, height };

		VkClearValue clearcolor[2];
		clearcolor[0].color = { {0.0f, 1.0f, 0.0f, 1.0f} };
		clearcolor[1].depthStencil = { 1.0f, 0 };

		renderpass_begin_info.clearValueCount = 2;
		renderpass_begin_info.pClearValues = clearcolor;

		return renderpass_begin_info;
	}
}
#endif // ENGINE_GRAPHIC_VULKAN