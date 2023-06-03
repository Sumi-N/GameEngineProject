#include "CommandBuffer.h"

#ifdef ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	void CommandBuffer::Init(const Device& i_device)
	{
		p_device = &i_device;

		VkCommandBufferAllocateInfo commandbuffer_allocate_info{};
		commandbuffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandbuffer_allocate_info.commandPool = p_device->commandpool;
		commandbuffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandbuffer_allocate_info.commandBufferCount = 1;

		VkResult create_commandbuffer_result = vkAllocateCommandBuffers(p_device->logical_device, &commandbuffer_allocate_info, &commandbuffer);
		DEBUG_ASSERT(create_commandbuffer_result == VK_SUCCESS);
	}

	void CommandBuffer::CleanUp()
	{
	}

	void CommandBuffer::ResetCommand() const
	{
		vkResetCommandBuffer(commandbuffer, 0);
	}

	void CommandBuffer::BeginCommand() const
	{
		VkCommandBufferBeginInfo begin_info{};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		begin_info.pInheritanceInfo = nullptr;

		auto begin_command_result = vkBeginCommandBuffer(commandbuffer, &begin_info);
		DEBUG_ASSERT(begin_command_result == VK_SUCCESS);
	}

	void CommandBuffer::BeginRenderPass(const FrameBuffer& i_framebuffer, const RenderPass& i_renderpass) const
	{
		VkClearValue clearcolor[2];
		clearcolor[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
		clearcolor[1].depthStencil = { 1.0f, 0 };

		VkRenderPassBeginInfo renderpass_begin_info{};
		{
			renderpass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderpass_begin_info.renderPass = i_renderpass.renderpass;
			renderpass_begin_info.framebuffer = i_framebuffer.framebuffer;
			renderpass_begin_info.renderArea.offset = { 0, 0 };
			renderpass_begin_info.renderArea.extent = { i_framebuffer.width, i_framebuffer.height };
			renderpass_begin_info.clearValueCount = 2;
			renderpass_begin_info.pClearValues = clearcolor;
		}

		vkCmdBeginRenderPass(commandbuffer, &renderpass_begin_info, VK_SUBPASS_CONTENTS_INLINE);

		{
			VkViewport viewport{};
			viewport.x = 0.0f;
			viewport.y = (float)i_framebuffer.height;
			viewport.width = (float)i_framebuffer.width;
			viewport.height = -1 * (float)i_framebuffer.height;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;
			vkCmdSetViewport(commandbuffer, 0, 1, &viewport);

			VkRect2D scissor{};
			scissor.offset = { 0, 0 };
			scissor.extent = VkExtent2D{ i_framebuffer.width, i_framebuffer.height };
			vkCmdSetScissor(commandbuffer, 0, 1, &scissor);
		}
	}

	void CommandBuffer::BindDescriptor(int i_index, const Descriptor& i_descriptor, const Pipeline& i_pipeline) const
	{
		vkCmdBindPipeline(commandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, i_pipeline.pipeline);

		vkCmdBindDescriptorSets(commandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, i_pipeline.pipeline_layout, 0, 1, &i_descriptor.descriptor_sets[i_index], 0, nullptr);
	}

	void CommandBuffer::Draw(const VertexBuffer& i_vertexbuffer) const
	{
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandbuffer, 0, 1, &i_vertexbuffer.vertexbuffer, offsets);
		vkCmdBindIndexBuffer(commandbuffer, i_vertexbuffer.indexbuffer, 0, VK_INDEX_TYPE_UINT32);
		vkCmdDrawIndexed(commandbuffer, i_vertexbuffer.indecies_count, 1, 0, 0, 0);
	}

	void CommandBuffer::EndRenderPass() const
	{
		vkCmdEndRenderPass(commandbuffer);
	}

	void CommandBuffer::EndCommand() const
	{
		auto end_command_result = vkEndCommandBuffer(commandbuffer);
		DEBUG_ASSERT(end_command_result == VK_SUCCESS);
	}
}
#endif // ENGINE_GRAPHIC_VULKAN
