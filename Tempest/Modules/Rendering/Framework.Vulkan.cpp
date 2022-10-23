#include "Define.h"
#include "Framework.h"
#include "Image_SpecularIBL.h"
#include "Image_DiffuseIrradianceIBL.h"

#include <vulkan/vulkan.h>

#ifdef ENGINE_GRAPHIC_VULKAN

namespace Tempest
{
	Device      Framework::device;
	SwapChain   Framework::swapchain;
	RenderPass  Framework::renderpass;
	FrameBuffer Framework::framebuffers[3];

	Pipeline pipeline;
	CommandBuffer commandbuffers[2];
	Shader shader;
	Descriptor descriptor;

	VertexBuffer vertexbuffer;
	VertexBuffer vertexbuffer2;
	UniformBuffer uniformbuffer_camera;
	UniformBuffer uniformbuffer_model;
	Texture texture;

	VkSemaphore image_available_semaphores[2];
	VkSemaphore render_finished_semaphores[2];
	VkFence in_flight_fences[2];
	uint32_t current_frame = 0;

	SpecularIBLImage specular_ibl_image;
	DiffuseIrradianceIBLImage diffuse_irradiance_ibl_image;

	BufferLayout vertex_layout;
	BufferLayout camera_uniform_layout;
	BufferLayout model_uniform_layout;

	void Framework::Boot(Window* i_window)
	{
		device.Init(i_window);
		swapchain.Init(device);
		commandbuffers[0].Init(device);
		commandbuffers[1].Init(device);
		renderpass.Init(device, swapchain);
		framebuffers[0].Init(device, renderpass, swapchain, 0);
		framebuffers[1].Init(device, renderpass, swapchain, 1);
		framebuffers[2].Init(device, renderpass, swapchain, 2);

		PrimitiveDrawer::Init();

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

	void Framework::Init(uint32_t, uint32_t)
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

		descriptor.Init(device, shader);

		BufferUnit vertex_mesh1{ BufferFormat::Float3, "vertex" };
		BufferUnit vertex_mesh2{ BufferFormat::Float3, "normal" };
		BufferUnit vertex_mesh3{ BufferFormat::Float2, "uv" };
		BufferUnit vertex_mesh4{ BufferFormat::Float3, "tangent" };
		BufferUnit vertex_mesh5{ BufferFormat::Float3, "bitangent" };
		vertex_layout.Init({ vertex_mesh1, vertex_mesh2, vertex_mesh3, vertex_mesh4, vertex_mesh5 });

		vertexbuffer.Init(device, vertex_layout, mesh.data.Data(), mesh.data.Size() * sizeof(mesh.data[0]), mesh.index.Data(), mesh.index.Size() * sizeof(mesh.index[0]));
		vertexbuffer2.Init(device, vertex_layout, mesh2.data.Data(), mesh2.data.Size() * sizeof(mesh2.data[0]), mesh2.index.Data(), mesh2.index.Size() * sizeof(mesh2.index[0]));

		BufferUnit const_camera1{ BufferFormat::Mat4, "view_matrix" };
		BufferUnit const_camera2{ BufferFormat::Mat4, "perspective_matrix" };
		BufferUnit const_camera3{ BufferFormat::Float3, "camera_position_vector" };
		BufferUnit const_camera4{ BufferFormat::Float, "camera_padding" };
		camera_uniform_layout.Init({ const_camera1, const_camera2, const_camera3, const_camera4 });
		uniformbuffer_camera.Init(device, camera_uniform_layout);

		BufferUnit const_model1{ BufferFormat::Mat4, "model_position_matrix" };
		BufferUnit const_model2{ BufferFormat::Mat4, "model_view_perspevtive_matrix" };
		BufferUnit const_model3{ BufferFormat::Mat3, "model_inverse_transpose_matrix" };
		model_uniform_layout.Init({ const_model1, const_model2, const_model3 });
		uniformbuffer_model.Init(device, model_uniform_layout);

		texture.Init(device, texture_info);

		descriptor.Bind(uniformbuffer_camera, 0);
		descriptor.Bind(uniformbuffer_model, 1);
		descriptor.Bind(texture, 2);

		pipeline.Init(device, shader, descriptor, renderpass, sizeof(MeshPoint));
	}

	void Framework::CleanUp()
	{

	}

	void Framework::PreCompute()
	{
		//specular_ibl_image.Init(device);
		//{
		//	commandbuffers[current_frame].BeginCommand();

		//	specular_ibl_image.BindFrameBuffer(commandbuffers[current_frame]);
		//	specular_ibl_image.BindDescriptor(commandbuffers[current_frame]);
		//	PrimitiveDrawer::DrawQuad(commandbuffers[current_frame]);

		//	commandbuffers[current_frame].EndCommand();

		//	VkSubmitInfo submit_info{};
		//	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		//	submit_info.commandBufferCount = 1;
		//	submit_info.pCommandBuffers = &commandbuffers[current_frame].commandbuffer;

		//	auto queue_submi_result = vkQueueSubmit(device.queue, 1, &submit_info, nullptr);
		//	DEBUG_ASSERT(queue_submi_result == VK_SUCCESS);

		//	vkQueueWaitIdle(device.queue);
		//}

		//diffuse_irradiance_ibl_image.Init(device);
		//{
		//	commandbuffers[current_frame].BeginCommand();

		//	diffuse_irradiance_ibl_image.BindFrameBuffer(commandbuffers[current_frame]);
		//	diffuse_irradiance_ibl_image.BindDescriptor(commandbuffers[current_frame]);
		//	PrimitiveDrawer::DrawCube(commandbuffers[current_frame]);

		//	commandbuffers[current_frame].EndCommand();

		//	VkSubmitInfo submit_info{};
		//	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		//	submit_info.commandBufferCount = 1;
		//	submit_info.pCommandBuffers = &commandbuffers[current_frame].commandbuffer;

		//	auto queue_submi_result = vkQueueSubmit(device.queue, 1, &submit_info, nullptr);
		//	DEBUG_ASSERT(queue_submi_result == VK_SUCCESS);
		//}
	}

	void Framework::PreUpdate(GraphicRequiredData* i_data)
	{

	}

	void Framework::Update(GraphicRequiredData* i_data)
	{
		vkWaitForFences(device.logical_device, 1, &in_flight_fences[current_frame], VK_TRUE, UINT64_MAX);

		uint32_t image_index;
		vkAcquireNextImageKHR(device.logical_device, swapchain.Get(), UINT64_MAX, image_available_semaphores[current_frame], VK_NULL_HANDLE, &image_index);

		vkResetFences(device.logical_device, 1, &in_flight_fences[current_frame]);


		{
			commandbuffers[current_frame].BeginCommand();

			commandbuffers[current_frame].BindFrameBuffer(framebuffers[image_index], renderpass);

			commandbuffers[current_frame].BindDescriptor(current_frame, descriptor, pipeline);

			uniformbuffer_camera.Update(current_frame, static_cast<void*>(&i_data->camera), sizeof(ConstantData::Camera), 0);
			if (i_data->model_data.Size() != 0) { uniformbuffer_model.Update(current_frame, static_cast<void*>(&i_data->model_data[0]), sizeof(ConstantData::Model), 0); }

			commandbuffers[current_frame].Draw(vertexbuffer);
			commandbuffers[current_frame].Draw(vertexbuffer2);

			commandbuffers[current_frame].EndCommand();
		}

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore wait_semaphores[] = { image_available_semaphores[current_frame] };
		VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = wait_semaphores;
		submitInfo.pWaitDstStageMask = wait_stages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandbuffers[current_frame].commandbuffer;

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

	void Framework::ChangeViewportSize(uint32_t i_width, uint32_t i_height)
	{
		/*ViewportWidth = i_width;
		ViewportHeight = i_height;*/
	}
}

#endif // ENGINE_GRAPHIC_VULKAN