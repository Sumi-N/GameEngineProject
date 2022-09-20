#include "Define.h"
#include "Framework.h"

#include <vulkan/vulkan.h>

#ifdef ENGINE_GRAPHIC_VULKAN

namespace Tempest
{
	Device device;
	Queue queue;
	SwapChain swapchain;
	Pipeline pipeline;
	CommandBuffer commandbuffers[2];
	Shader shader;
	VertexBuffer vertexbuffer;
	UniformBuffer uniformbuffer;
	FrameBuffer framebuffer;
	VkSemaphore image_available_semaphores[2];
	VkSemaphore render_finished_semaphores[2];
	VkFence in_flight_fences[2];
	uint32_t current_frame = 0;

	void Framework::Boot(Window* i_window)
	{
		Mesh mesh;
		Mesh::Load("", mesh);

		//Shader::Load("D:/GameEngineProject/Assets/bin/shader/basic.ts", shader);
		Shader::Load("D:/GameEngineProject/Assets/bin/shader/outlinehighlight.ts", shader);
		device.Init(i_window);
		queue.Init(device);
		swapchain.Init(device);
		vertexbuffer.Init(device, shader);
		commandbuffers[0].Init(device);
		commandbuffers[1].Init(device);
		vertexbuffer.InitData(commandbuffers[0], mesh.data.Data(), mesh.data.Size(), mesh.index.Data(), mesh.index.Size());
		uniformbuffer.Init(device, shader);
		pipeline.Init(device, swapchain, shader, vertexbuffer, uniformbuffer);
		framebuffer.Init(device, swapchain, pipeline);

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		if (vkCreateSemaphore(device.logical_device, &semaphoreInfo, nullptr, &image_available_semaphores[0]) != VK_SUCCESS ||
			vkCreateSemaphore(device.logical_device, &semaphoreInfo, nullptr, &render_finished_semaphores[0]) != VK_SUCCESS ||
			vkCreateFence(device.logical_device, &fenceInfo, nullptr, &in_flight_fences[0]) != VK_SUCCESS)
		{

			throw std::runtime_error("failed to create semaphores!");
		}

		if (vkCreateSemaphore(device.logical_device, &semaphoreInfo, nullptr, &image_available_semaphores[1]) != VK_SUCCESS ||
			vkCreateSemaphore(device.logical_device, &semaphoreInfo, nullptr, &render_finished_semaphores[1]) != VK_SUCCESS ||
			vkCreateFence(device.logical_device, &fenceInfo, nullptr, &in_flight_fences[1]) != VK_SUCCESS)
		{

			throw std::runtime_error("failed to create semaphores!");
		}
	}

	void Framework::CleanUp()
	{

	}

	void Framework::PreCompute()
	{

	}

	void Framework::PreUpdate(GraphicRequiredData* i_data)
	{

	}

	void Framework::Update(GraphicRequiredData* i_data)
	{
		vkWaitForFences(device.logical_device, 1, &in_flight_fences[current_frame], VK_TRUE, UINT64_MAX);
		vkResetFences(device.logical_device, 1, &in_flight_fences[current_frame]);

		uint32_t image_index;
		vkAcquireNextImageKHR(device.logical_device, swapchain.swapchain, UINT64_MAX, image_available_semaphores[current_frame], VK_NULL_HANDLE, &image_index);

		vkResetCommandBuffer(commandbuffers->commandbuffers[current_frame], /*VkCommandBufferResetFlagBits*/ 0);

		{
			VkCommandBufferBeginInfo begin_info{};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags = 0;
			begin_info.pInheritanceInfo = nullptr;

			if (vkBeginCommandBuffer(commandbuffers->commandbuffers[current_frame], &begin_info) != VK_SUCCESS)
			{
				DEBUG_ASSERT(false);
			}

			VkRenderPassBeginInfo renderpass_info{};
			renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderpass_info.renderPass = pipeline.render_pass;
			renderpass_info.framebuffer = framebuffer.framebuffers[image_index];
			renderpass_info.renderArea.offset = { 0, 0 };
			renderpass_info.renderArea.extent = { 1920, 1080 };

			VkClearValue clearcolor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
			renderpass_info.clearValueCount = 1;
			renderpass_info.pClearValues = &clearcolor;

			vkCmdBeginRenderPass(commandbuffers->commandbuffers[current_frame], &renderpass_info, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(commandbuffers->commandbuffers[current_frame], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.graphics_pipeline);
			vkCmdDraw(commandbuffers->commandbuffers[current_frame], 3, 1, 0, 0);
			vkCmdEndRenderPass(commandbuffers->commandbuffers[current_frame]);
			if (vkEndCommandBuffer(commandbuffers->commandbuffers[current_frame]) != VK_SUCCESS)
			{
				DEBUG_ASSERT(false);
			}
		}

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore wait_semaphores[] = { image_available_semaphores[current_frame] };
		VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = wait_semaphores;
		submitInfo.pWaitDstStageMask = wait_stages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandbuffers->commandbuffers[current_frame];

		VkSemaphore signal_semaphores[] = { render_finished_semaphores[current_frame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signal_semaphores;

		if (vkQueueSubmit(queue.graphics_queue, 1, &submitInfo, in_flight_fences[current_frame]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to submit draw command buffer!");
		}

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signal_semaphores;

		VkSwapchainKHR swapChains[] = { swapchain.swapchain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &image_index;

		vkQueuePresentKHR(queue.present_queue, &presentInfo);

		current_frame = 1 - current_frame;
	}

	void Framework::PostUpdate(GraphicRequiredData* i_data)
	{
		i_data->model_data.Clear();
		i_data->material_data.Clear();
	}
}

#endif // ENGINE_GRAPHIC_VULKAN