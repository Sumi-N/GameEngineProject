#include "FrameBuffer.h"
#include "Device.h"

void FrameBuffer::Init(FrameType i_type, int i_unitnum, int i_width, int i_height)
{
	framebuffers.Resize(swapchain_image_views.Size());
	for (size_t i = 0; i < swapchain_image_views.Size(); i++)
	{
		VkImageView attachments[] = { swapchain_image_views[i] };

		VkFramebufferCreateInfo framebuffer_create_info{};
		framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebuffer_create_info.renderPass = render_pass;
		framebuffer_create_info.attachmentCount = 1;
		framebuffer_create_info.pAttachments = attachments;
		framebuffer_create_info.width = support_details.extent.width;
		framebuffer_create_info.height = support_details.extent.height;
		framebuffer_create_info.layers = 1;

		if (vkCreateFramebuffer(logical_device, &framebuffer_create_info, nullptr, &framebuffers[i]) != VK_SUCCESS)
		{
			DEBUG_ASSERT(false);
		}
	}
}