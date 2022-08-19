#include "Graphic.h"
#include "Device.h"
#include "Queue.h"
#include "SwapChain.h"
#include "Pipeline.h"
#include "CommandBuffer.h"

#ifdef ENGINE_GRAPHIC_VULKAN

namespace Tempest
{
	Device device;
	Queue queue;
	SwapChain swapchain;
	Pipeline pipeline;
	CommandBuffer commandbuffers[2];
	VkSemaphore imageAvailableSemaphores[2];
	VkSemaphore renderFinishedSemaphores[2];
	VkFence inFlightFences[2];
	uint32_t currentFrame = 0;

	void Graphic::Boot(Window* i_window)
	{
		device.Initialize(i_window);
		queue.Initialize(device);
		swapchain.Initialize(device);

	}

	void Graphic::PreCompute()
	{

	}

	void Graphic::PreUpdate(GraphicRequiredData* i_data)
	{

	}

	void Graphic::Update(GraphicRequiredData* i_data)
	{
		vkWaitForFences(device.logical_device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
		vkResetFences(device.logical_device, 1, &inFlightFences[currentFrame]);

		uint32_t imageIndex;
		vkAcquireNextImageKHR(device.logical_device, swapchain.swapchain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

		vkResetCommandBuffer(commandbuffers->commandbuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);

		{
			VkCommandBufferBeginInfo begin_info{};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags = 0;
			begin_info.pInheritanceInfo = nullptr;

			if (vkBeginCommandBuffer(commandbuffers->commandbuffers[currentFrame], &begin_info) != VK_SUCCESS)
			{
				DEBUG_ASSERT(false);
			}

			VkRenderPassBeginInfo renderpass_info{};
			renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderpass_info.renderPass = pipeline.render_pass;
			renderpass_info.framebuffer = swapchain_framebuffers[image_index];
			renderpass_info.renderArea.offset = { 0, 0 };
			renderpass_info.renderArea.extent = { 1920, 1080 };

			VkClearValue clearcolor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
			renderpass_info.clearValueCount = 1;
			renderpass_info.pClearValues = &clearcolor;

			vkCmdBeginRenderPass(commandbuffers->commandbuffers[currentFrame], &renderpass_info, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(commandbuffers->commandbuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, graphics_pipeline);
			vkCmdDraw(commandbuffers->commandbuffers[currentFrame], 3, 1, 0, 0);
			vkCmdEndRenderPass(commandbuffers->commandbuffers[currentFrame]);
			if (vkEndCommandBuffer(commandbuffers->commandbuffers[currentFrame]) != VK_SUCCESS)
			{
				DEBUG_ASSERT(false);
			}
		}

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandbuffers->commandbuffers[currentFrame];

		VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if (vkQueueSubmit(graphics_queue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to submit draw command buffer!");
		}

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = { swapchain.swapchain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &imageIndex;

		vkQueuePresentKHR(present_queue, &presentInfo);

		currentFrame = 1 - currentFrame;
	}

	void Graphic::PostUpdate(GraphicRequiredData* i_data)
	{
		i_data->model_data.Clear();
		i_data->material_data.Clear();
	}

	void Graphic::CleanUp()
	{

	}
}

#endif // ENGINE_GRAPHIC_VULKAN