#include "FrameBuffer.h"

namespace Tempest
{
	void FrameBuffer::Init(FrameType i_type, int i_unitnum, int i_width, int i_height)
	{
	}

	void FrameBuffer::Initialize(const Device& i_device, const SwapChain& i_swapchain, const Pipeline& i_pipeline)
	{
		framebuffers.Resize(i_swapchain.swapchain_image_views.Size());
		for (size_t i = 0; i < i_swapchain.swapchain_image_views.Size(); i++)
		{
			VkImageView attachments[] = { i_swapchain.swapchain_image_views[i] };

			VkFramebufferCreateInfo framebuffer_create_info{};
			framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebuffer_create_info.renderPass = i_pipeline.render_pass;
			framebuffer_create_info.attachmentCount = 1;
			framebuffer_create_info.pAttachments = attachments;
			framebuffer_create_info.width = i_swapchain.support_details.extent.width;
			framebuffer_create_info.height = i_swapchain.support_details.extent.height;
			framebuffer_create_info.layers = 1;

			const VkResult& result = vkCreateFramebuffer(i_device.logical_device, &framebuffer_create_info, nullptr, &framebuffers[i]);
			DEBUG_ASSERT(result == VK_SUCCESS);
		}
	}
}