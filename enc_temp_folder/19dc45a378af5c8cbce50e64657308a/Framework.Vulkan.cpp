#include "Define.h"
#include "Framework.h"

#include <vulkan/vulkan.h>

#ifdef ENGINE_GRAPHIC_VULKAN

namespace Tempest
{
	Device device;
	SwapChain swapchain;
	Pipeline pipeline;
	CommandBuffer commandbuffers[2];
	Shader shader;
	Descriptor descriptor;
	RenderPass renderpass;
	FrameBuffer framebuffers[3];

	VertexBuffer vertexbuffer;
	VertexBuffer vertexbuffer2;
	UniformBuffer uniformbuffer_camera;
	UniformBuffer uniformbuffer_model;
	Texture texture;

	VkSemaphore image_available_semaphores[2];
	VkSemaphore render_finished_semaphores[2];
	VkFence in_flight_fences[2];
	uint32_t current_frame = 0;

	Pipeline pipeline_ibl;
	Shader shader_ibl;
	Texture texture_ibl;
	RenderPass renderpass_ibl;
	FrameBuffer framebuffer_ibl;

	void Framework::Boot(Window* i_window)
	{
		Mesh mesh;
		Mesh::Load("D:/GameEngineProject/Assets/bin/mesh/SK_PlayerCharacter.tm", mesh);

		Mesh mesh2;
		Mesh::Load("D:/GameEngineProject/Assets/bin/mesh/teapot.tm", mesh2);
		TextureInfo texture_info;
		TextureInfo::Load("D:/GameEngineProject/Assets/bin/texture/albedo/CharacterBody_BaseColor.tt", texture_info);

		//Shader::Load("D:/GameEngineProject/Assets/bin/shader/basic.ts", shader);
		//Shader::Load("D:/GameEngineProject/Assets/bin/shader/outlinehighlight.ts", shader);
		Shader::Load("D:/GameEngineProject/Assets/bin/shader/albedomodel.ts", shader);
		device.Init(i_window);
		swapchain.Init(device);
		commandbuffers[0].Init(device);
		commandbuffers[1].Init(device);
		descriptor.Init(device, shader);
		renderpass.Init(device, swapchain);
		framebuffers[0].Init(device, renderpass, swapchain, 0);
		framebuffers[1].Init(device, renderpass, swapchain, 1);
		framebuffers[2].Init(device, renderpass, swapchain, 2);

		vertexbuffer.Init(device, shader);
		vertexbuffer2.Init(device, shader);
		vertexbuffer.InitData(mesh.data.Data(), mesh.data.Size() * sizeof(mesh.data[0]), mesh.index.Data(), mesh.index.Size() * sizeof(mesh.index[0]));
		vertexbuffer2.InitData(mesh2.data.Data(), mesh2.data.Size() * sizeof(mesh2.data[0]), mesh2.index.Data(), mesh2.index.Size() * sizeof(mesh2.index[0]));

		BufferUnit const_camera1{BufferFormat::Mat3, "view_matrix"};
		BufferUnit const_camera2{ BufferFormat::Mat4, "perspective_matrix" };
		BufferUnit const_camera3{ BufferFormat::Float3, "camera_position_vector" };
		BufferUnit const_camera4{ BufferFormat::Float, "camera_padding" };
		BufferLayout camera_uniform_layout(device, BufferType::Uniform, {const_camera1, const_camera2, const_camera3, const_camera4});
		uniformbuffer_camera.Init(device, camera_uniform_layout);

		BufferUnit const_model1{ BufferFormat::Mat4, "model_position_matrix" };
		BufferUnit const_model2{ BufferFormat::Mat4, "model_view_perspevtive_matrix" };
		BufferUnit const_model3{ BufferFormat::Mat3, "model_inverse_transpose_matrix" };
		BufferLayout model_uniform_layout(device, BufferType::Uniform, { const_model1, const_model2, const_model3});
		uniformbuffer_model.Init(device, model_uniform_layout);

		texture.Init(device, texture_info);

		descriptor.Bind(uniformbuffer_camera, 0);
		descriptor.Bind(uniformbuffer_model, 1);
		descriptor.Bind(texture, 2);

		pipeline.Init(device, swapchain, shader, vertexbuffer, descriptor, renderpass);

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
		Shader::Load("D:/GameEngineProject/Assets/bin/shader/brdf_integration_map.ts", shader_ibl);
		TextureInfo texture_info_ibl{};
		{
			texture_info_ibl.width = 512;
			texture_info_ibl.height = 512;
			texture_info_ibl.sampler_needed = true;
			texture_info_ibl.has_data = false;
			texture_info_ibl.format = TextureFormat::R16G16_SFLOAT;
			texture_info_ibl.usage_flag = USAGE_COLOR_ATTACHMENT_BIT;
			texture_info_ibl.aspect_flag = COLOR_BIT_ASPECT;
		}
		Mesh mesh_ibl;
		Mesh::Load("D:/GameEngineProject/Assets/bin/mesh/cubemap.tm", mesh_ibl);
		texture_ibl.Init(device, texture_info_ibl);
		renderpass_ibl.Init(device, texture_ibl);
		framebuffer_ibl.Init(device, renderpass_ibl, texture_ibl);
		//pipeline_ibl.Init(device, swapchain, shader, vertexbuffer, uniformbuffer, renderpass);

		vkResetCommandBuffer(commandbuffers[0].GetBuffer(), 0);

		/*{
			VkCommandBufferBeginInfo begin_info{};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			begin_info.pInheritanceInfo = nullptr;

			auto begin_command_result = vkBeginCommandBuffer(commandbuffer.GetBuffer(0), &begin_info);
			DEBUG_ASSERT(begin_command_result == VK_SUCCESS);

			VkRenderPassBeginInfo renderpass_begin_info{};
			{
				renderpass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
				renderpass_begin_info.renderPass = renderpass_ibl.GetRenderPass();
				renderpass_begin_info.framebuffer = framebuffer_ibl.GetBuffer();
				renderpass_begin_info.renderArea.offset = { 0, 0 };
				renderpass_begin_info.renderArea.extent = { 512, 512 };

				VkClearValue clearcolor[2];
				clearcolor[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };

				renderpass_begin_info.clearValueCount = 1;
				renderpass_begin_info.pClearValues = clearcolor;

				vkCmdBeginRenderPass(commandbuffer.GetBuffer(0), &renderpass_begin_info, VK_SUBPASS_CONTENTS_INLINE);
				vkCmdBindPipeline(commandbuffer.GetBuffer(0), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.GetPipeline());

				VkDeviceSize offsets[] = { 0 };
				vkCmdBindVertexBuffers(commandbuffer.GetBuffer(current_frame), 0, 1, &vertexbuffer.vertexbuffer, offsets);
				vkCmdBindIndexBuffer(commandbuffer.GetBuffer(current_frame), vertexbuffer.indexbuffer, 0, VK_INDEX_TYPE_UINT32);
				vkCmdBindDescriptorSets(commandbuffer.GetBuffer(current_frame), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.GetPipelineLayout(), 0, 1, &uniformbuffer.GetDescriptorSet(current_frame), 0, nullptr);
				vkCmdDrawIndexed(commandbuffer.GetBuffer(current_frame), vertexbuffer.index_coount, 1, 0, 0, 0);

				vkCmdEndRenderPass(commandbuffer.GetBuffer(0));
				auto end_command_result = vkEndCommandBuffer(commandbuffer.GetBuffer(0));
				DEBUG_ASSERT(end_command_result == VK_SUCCESS);

				auto queue_submi_result = vkQueueSubmit(device.graphics_queue, 1, nullptr, nullptr);
				DEBUG_ASSERT(queue_submi_result == VK_SUCCESS);
			}
		}*/
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

		vkResetCommandBuffer(commandbuffers[current_frame].GetBuffer(), 0);

		{
			VkCommandBufferBeginInfo begin_info{};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags = 0;
			begin_info.pInheritanceInfo = nullptr;

			auto begin_command_result = vkBeginCommandBuffer(commandbuffers[current_frame].GetBuffer(), &begin_info);
			DEBUG_ASSERT(begin_command_result == VK_SUCCESS);

			VkRenderPassBeginInfo renderpass_begin_info{};
			{
				renderpass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
				renderpass_begin_info.renderPass = renderpass.render_pass;
				renderpass_begin_info.framebuffer = framebuffers[image_index].GetBuffer();
				renderpass_begin_info.renderArea.offset = { 0, 0 };
				renderpass_begin_info.renderArea.extent = { 1920, 1080 };

				VkClearValue clearcolor[2];
				clearcolor[0].color = { {0.0f, 1.0f, 0.0f, 1.0f} };
				clearcolor[1].depthStencil = { 1.0f, 0 };

				renderpass_begin_info.clearValueCount = 2;
				renderpass_begin_info.pClearValues = clearcolor;
			}

			vkCmdBeginRenderPass(commandbuffers[current_frame].GetBuffer(), &renderpass_begin_info, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(commandbuffers[current_frame].GetBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);

			uniformbuffer_camera.Update(current_frame, static_cast<void*>(&i_data->camera), sizeof(ConstantData::Camera), 0);

			if (i_data->model_data.Size() != 0)
			{
				uniformbuffer_model.Update(current_frame, static_cast<void*>(&i_data->model_data[0]), sizeof(ConstantData::Model), 0);
			}
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandbuffers[current_frame].GetBuffer(), 0, 1, &vertexbuffer.vertexbuffer, offsets);
			vkCmdBindIndexBuffer(commandbuffers[current_frame].GetBuffer(), vertexbuffer.indexbuffer, 0, VK_INDEX_TYPE_UINT32);
			vkCmdBindDescriptorSets(commandbuffers[current_frame].GetBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline_layout, 0, 1, &descriptor.descriptor_sets[current_frame], 0, nullptr);
			vkCmdDrawIndexed(commandbuffers[current_frame].GetBuffer(), vertexbuffer.index_coount, 1, 0, 0, 0);

			vkCmdBindVertexBuffers(commandbuffers[current_frame].GetBuffer(), 0, 1, &vertexbuffer2.vertexbuffer, offsets);
			vkCmdBindIndexBuffer(commandbuffers[current_frame].GetBuffer(), vertexbuffer2.indexbuffer, 0, VK_INDEX_TYPE_UINT32);
			vkCmdDrawIndexed(commandbuffers[current_frame].GetBuffer(), vertexbuffer2.index_coount, 1, 0, 0, 0);

			vkCmdEndRenderPass(commandbuffers[current_frame].GetBuffer());
			auto end_command_result = vkEndCommandBuffer(commandbuffers[current_frame].GetBuffer());
			DEBUG_ASSERT(end_command_result == VK_SUCCESS);
		}

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore wait_semaphores[] = { image_available_semaphores[current_frame] };
		VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = wait_semaphores;
		submitInfo.pWaitDstStageMask = wait_stages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandbuffers[current_frame].GetBuffer();

		VkSemaphore signal_semaphores[] = { render_finished_semaphores[current_frame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signal_semaphores;

		auto queue_submi_result = vkQueueSubmit(device.queue, 1, &submitInfo, in_flight_fences[current_frame]);
		DEBUG_ASSERT(queue_submi_result == VK_SUCCESS);

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signal_semaphores;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &swapchain.Get();
		presentInfo.pImageIndices = &image_index;

		vkQueuePresentKHR(device.queue, &presentInfo);

		current_frame = 1 - current_frame;
	}

	void Framework::PostUpdate(GraphicRequiredData* i_data)
	{
		i_data->model_data.Clear();
		i_data->material_data.Clear();
	}
}

#endif // ENGINE_GRAPHIC_VULKAN