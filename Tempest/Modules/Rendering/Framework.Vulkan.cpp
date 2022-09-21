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
	CommandBuffer commandbuffer;
	Shader shader;
	VertexBuffer vertexbuffer;
	UniformBuffer uniformbuffer;
	FrameBuffer framebuffer;
	Texture texture;
	VkSemaphore image_available_semaphores[2];
	VkSemaphore render_finished_semaphores[2];
	VkFence in_flight_fences[2];
	uint32_t current_frame = 0;

	void Framework::Boot(Window* i_window)
	{
		Mesh mesh;
		Mesh::Load("D:/GameEngineProject/Assets/bin/mesh/SK_PlayerCharacter.tm", mesh);
		TextureInfo texture_info;
		TextureInfo::Load("D:/GameEngineProject/Assets/bin/texture/albedo/CharacterBody_BaseColor.tt", texture_info);

		//Shader::Load("D:/GameEngineProject/Assets/bin/shader/basic.ts", shader);
		//Shader::Load("D:/GameEngineProject/Assets/bin/shader/outlinehighlight.ts", shader);
		Shader::Load("D:/GameEngineProject/Assets/bin/shader/albedomodel.ts", shader);
		device.Init(i_window);
		queue.Init(device);
		swapchain.Init(device);
		vertexbuffer.Init(device, shader);
		commandbuffer.Init(device);
		texture.Init(device, commandbuffer, texture_info);
		uniformbuffer.Init(device, shader, texture);
		pipeline.Init(device, swapchain, shader, vertexbuffer, uniformbuffer);
		framebuffer.Init(device, swapchain, pipeline);

		vertexbuffer.InitData(commandbuffer, mesh.data.Data(), mesh.data.Size() * sizeof(mesh.data[0]), mesh.index.Data(), mesh.index.Size() * sizeof(mesh.index[0]));

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
		vkAcquireNextImageKHR(device.logical_device, swapchain.Get(), UINT64_MAX, image_available_semaphores[current_frame], VK_NULL_HANDLE, &image_index);

		vkResetCommandBuffer(commandbuffer.GetBuffer(current_frame), /*VkCommandBufferResetFlagBits*/ 0);

		{
			VkCommandBufferBeginInfo begin_info{};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags = 0;
			begin_info.pInheritanceInfo = nullptr;

			if (vkBeginCommandBuffer(commandbuffer.GetBuffer(current_frame), &begin_info) != VK_SUCCESS)
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

			vkCmdBeginRenderPass(commandbuffer.GetBuffer(current_frame), &renderpass_info, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(commandbuffer.GetBuffer(current_frame), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.graphics_pipeline);

			void* this_data3 = static_cast<void*>(&i_data->camera);
			Mat4f* view = (Mat4f*)(this_data3);
			view[0] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, 0, -1), Vec3f(0, 1, 0));
			view[1] = Mat4f::Perspective(FieldOfView, (float)ScreenWidth / ScreenHeight, NearClip, FarClip);

			uniformbuffer.Update(current_frame, static_cast<void*>(&i_data->camera), sizeof(ConstantData::Camera), 0);

			void* this_data = static_cast<void*>(&i_data->camera);
			Mat4f* this_data2 = (Mat4f*)(this_data);
			this_data2[0] = Mat4f{};
			this_data2[0] = this_data2[0].Scale(0.35);
			this_data2[0].ele[13] = -25;
			this_data2[0].ele[14] = -70;

			uniformbuffer.Update(current_frame, static_cast<void*>(&i_data->camera), sizeof(ConstantData::Model), 256);
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandbuffer.GetBuffer(current_frame), 0, 1, &vertexbuffer.vertexbuffer, offsets);
			vkCmdBindIndexBuffer(commandbuffer.GetBuffer(current_frame), vertexbuffer.indexbuffer, 0, VK_INDEX_TYPE_UINT32);
			vkCmdBindDescriptorSets(commandbuffer.GetBuffer(current_frame), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline_layout, 0, 1, &uniformbuffer.GetDescriptorSet(current_frame), 0, nullptr);
			vkCmdDrawIndexed(commandbuffer.GetBuffer(current_frame), vertexbuffer.index_coount, 1, 0, 0, 0);

			vkCmdEndRenderPass(commandbuffer.GetBuffer(current_frame));
			if (vkEndCommandBuffer(commandbuffer.GetBuffer(current_frame)) != VK_SUCCESS)
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
		submitInfo.pCommandBuffers = &commandbuffer.GetBuffer(current_frame);

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

		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &swapchain.Get();

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