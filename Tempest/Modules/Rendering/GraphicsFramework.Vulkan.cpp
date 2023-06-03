#include "Define.h"
#include "GraphicsFramework.h"
#include "RenderPass_SpecularIBL.h"
#include "RenderPass_Cubemap.h"
#include "RenderPass_Shadowmap.h"
#include "RenderPass_DiffuseConvolution.h"
#include "RenderPass_SpecularConvolution.h"

#include <vulkan/vulkan.h>

#ifdef ENGINE_GRAPHIC_VULKAN

namespace Tempest
{
	Pipeline pipeline;
	ShaderInfo shader;
	Descriptor descriptor;

	VertexBuffer vertexbuffer;
	VertexBuffer vertexbuffer2;
	VertexBuffer skyboxvertexbuffer;
	UniformBuffer uniformbuffer_camera;
	UniformBuffer uniformbuffer_model;
	UniformBuffer uniformbuffer_light;
	UniformBuffer uniformbuffer_skybox;
	Texture texture;
	Texture normal;
	Texture metallic;
	Texture roughness;

	SpecularIBLImage specular_ibl_image;
	CubemapImage cubemap_image;
	ShadowmapImage shadowmap_image;
	DiffuseConvolutionImage diffuse_convolution_image;
	SpecularConvolutionImage specular_convolution_image;

	BufferLayout vertex_layout;
	BufferLayout camera_uniform_layout;
	BufferLayout model_uniform_layout;
	BufferLayout light_uniform_layout;
	BufferLayout skybox_uniform_layout;

	Pipeline skybox_pipeline;
	ShaderInfo skybox_shader;
	Descriptor skybox_descriptor;

	void GraphicsFramework::Boot(Window* i_window)
	{
		currentFrame = 0;

		device.Init(i_window);
		swapChain.Init(device);
		for (int i = 0; i < Graphics::BufferingCount; i++)
		{
			commandBuffers[i].Init(device);
		}
		renderPass.Init(device, swapChain);
		frameBuffers.Resize(swapChain.GetImages().Size());
		for (int i = 0; i < frameBuffers.Size(); i++)
		{
			frameBuffers[i].Init(device, renderPass, swapChain, i);
		}

		for (int i = 0; i < Graphics::BufferingCount; i++)
		{
			frameworkFence[i].Init(device);
			imageDoneSemaphore[i].Init(device);
			presentableSemaphore[i].Init(device);
		}

		PrimitiveDrawer::Init(&device);
	}

	void GraphicsFramework::Init(uint32_t, uint32_t)
	{
		Mesh skybox;
		Mesh::Load(PATH_SUFFIX BIN_MESH_PATH "cubemap.tm", skybox);

		Mesh mesh;
		Mesh::Load(PATH_SUFFIX BIN_MESH_PATH "xbot.tm", mesh);

		Mesh mesh2;
		Mesh::Load(PATH_SUFFIX BIN_MESH_PATH "sphere.tm", mesh2);
		TextureInfo texture_info;
		TextureInfo::Load(PATH_SUFFIX BIN_TEXTURE_PATH "albedo/gold-scuffed_basecolor-boosted.tt", texture_info);
		TextureInfo normal_info;
		TextureInfo::Load(PATH_SUFFIX BIN_TEXTURE_PATH "normal/brushed-metal_normal-dx.tt", normal_info);
		TextureInfo roughness_info;
		TextureInfo::Load(PATH_SUFFIX BIN_TEXTURE_PATH "roughness/brushed-metal_roughness.tt", roughness_info);
		TextureInfo metallic_info;
		TextureInfo::Load(PATH_SUFFIX BIN_TEXTURE_PATH "metallic/gray-bricks1-Metallic.tt", metallic_info);

		ShaderInfo::Load(PATH_SUFFIX BIN_SHADER_PATH "disney_pbr.ts", shader);

		descriptor.Init(device, shader);

		BufferUnit vertex_mesh1{ BufferFormat::Float3, "vertex" };
		BufferUnit vertex_mesh2{ BufferFormat::Float3, "normal" };
		BufferUnit vertex_mesh3{ BufferFormat::Float2, "texcoord" };
		BufferUnit vertex_mesh4{ BufferFormat::Float3, "tangent" };
		BufferUnit vertex_mesh5{ BufferFormat::Float3, "bitangent" };
		vertex_layout.Init({ vertex_mesh1, vertex_mesh2, vertex_mesh3, vertex_mesh4, vertex_mesh5 });

		vertexbuffer.Init(device, vertex_layout, mesh.data.Data(), mesh.data.Size() * sizeof(mesh.data[0]), mesh.index.Data(), mesh.index.Size() * sizeof(mesh.index[0]));
		vertexbuffer2.Init(device, vertex_layout, mesh2.data.Data(), mesh2.data.Size() * sizeof(mesh2.data[0]), mesh2.index.Data(), mesh2.index.Size() * sizeof(mesh2.index[0]));
		skyboxvertexbuffer.Init(device, vertex_layout, skybox.data.Data(), skybox.data.Size() * sizeof(skybox.data[0]), skybox.index.Data(), skybox.index.Size() * sizeof(skybox.index[0]));

		BufferUnit const_camera1{ BufferFormat::Mat4, "view_matrix" };
		BufferUnit const_camera2{ BufferFormat::Mat4, "perspective_matrix" };
		BufferUnit const_camera3{ BufferFormat::Float3, "camera_position_vector" };
		BufferUnit const_camera4{ BufferFormat::Float, "camera_padding" };
		camera_uniform_layout.Init({ const_camera1, const_camera2, const_camera3, const_camera4 });
		uniformbuffer_camera.Init(device, camera_uniform_layout);

		BufferUnit const_model1{ BufferFormat::Mat4, "model_position_matrix" };
		BufferUnit const_model2{ BufferFormat::Mat4, "model_view_perspevtive_matrix" };
		BufferUnit const_model3{ BufferFormat::Mat4, "model_inverse_transpose_matrix" };
		model_uniform_layout.Init({ const_model1, const_model2, const_model3 });
		uniformbuffer_model.Init(device, model_uniform_layout);

		BufferUnit const_light1{ BufferFormat::Float4, "ambient_intensity" };
		BufferUnit const_light2{ BufferFormat::Float4, "directional_intensity" };
		BufferUnit const_light3{ BufferFormat::Float4, "directional_direction" };
		BufferUnit const_light4{ BufferFormat::Float4x3, "pointlight_1" };
		BufferUnit const_light5{ BufferFormat::Float4x3, "pointlight_2" };
		BufferUnit const_light6{ BufferFormat::Float4x3, "pointlight_3" };
		BufferUnit const_light7{ BufferFormat::Float4x3, "pointlight_4" };
		BufferUnit const_light8{ BufferFormat::Float4x3, "pointlight_5" };
		BufferUnit const_light9{ BufferFormat::Int, "pointlight_num" };
		light_uniform_layout.Init({ const_light1, const_light2, const_light3, const_light4, const_light5, const_light6, const_light7, const_light8, const_light9 });
		uniformbuffer_light.Init(device, light_uniform_layout);

		texture.Init(device, texture_info);
		normal.Init(device, normal_info);
		roughness.Init(device, roughness_info);
		metallic.Init(device, metallic_info);

		descriptor.Bind(vertexbuffer);
		descriptor.Bind(uniformbuffer_camera, 0);
		descriptor.Bind(uniformbuffer_model, 1);
		descriptor.Bind(uniformbuffer_light, 3);
		descriptor.Bind(uniformbuffer_light, 4);
		descriptor.Bind(texture, 41);
		descriptor.Bind(normal, 42);
		descriptor.Bind(roughness, 43);
		descriptor.Bind(metallic, 44);

		pipeline.Init(device, descriptor, renderPass);
	}

	void GraphicsFramework::CleanUp()
	{

	}

	void GraphicsFramework::PreCompute()
	{
		CommandBuffer onetime_commandbuffer;
		onetime_commandbuffer.Init(device);

		cubemap_image.Init(device);
		shadowmap_image.Init(device);
		{
			onetime_commandbuffer.ResetCommand();
			onetime_commandbuffer.BeginCommand();

			cubemap_image.BeginRenderPass(onetime_commandbuffer);
			cubemap_image.BindDescriptor(onetime_commandbuffer);
			PrimitiveDrawer::DrawCube(onetime_commandbuffer);
			onetime_commandbuffer.EndRenderPass();

			shadowmap_image.BeginRenderPass(onetime_commandbuffer);
			shadowmap_image.BindDescriptor(onetime_commandbuffer);
			PrimitiveDrawer::DrawCube(onetime_commandbuffer);
			onetime_commandbuffer.EndRenderPass();

			onetime_commandbuffer.EndCommand();

			frameworkFence[0].Reset();
			device.SubmitToQueue(onetime_commandbuffer, &frameworkFence[0], nullptr, nullptr);
		}

		specular_ibl_image.Init(device);
		specular_convolution_image.Init(device, cubemap_image.cubemap_texture);
		diffuse_convolution_image.Init(device, cubemap_image.cubemap_texture);
		{
			frameworkFence[currentFrame].Wait();
			frameworkFence[currentFrame].Reset();
			onetime_commandbuffer.ResetCommand();
			onetime_commandbuffer.BeginCommand();

			specular_ibl_image.BeginRenderPass(onetime_commandbuffer);
			specular_ibl_image.BindDescriptor(onetime_commandbuffer);
			PrimitiveDrawer::DrawQuad(onetime_commandbuffer);
			onetime_commandbuffer.EndRenderPass();

			for (int i = 0; i < 5; i++)
			{
				float roughness = 0.0f;
				specular_convolution_image.BeginRenderPass(onetime_commandbuffer, i);
				specular_convolution_image.BindDescriptor(onetime_commandbuffer);
				specular_convolution_image.roughness_uniform.Update(0, static_cast<void*>(&roughness), sizeof(float), 0);
				PrimitiveDrawer::DrawCube(onetime_commandbuffer);
				onetime_commandbuffer.EndRenderPass();
			}

			diffuse_convolution_image.BeginRenderPass(onetime_commandbuffer);
			diffuse_convolution_image.BindDescriptor(onetime_commandbuffer);
			PrimitiveDrawer::DrawCube(onetime_commandbuffer);
			onetime_commandbuffer.EndRenderPass();

			onetime_commandbuffer.EndCommand();

			device.SubmitToQueue(onetime_commandbuffer, &frameworkFence[0], nullptr, nullptr);
		}

		BufferUnit const_skybox{ BufferFormat::Mat4, "view_perspective_matrix" };
		skybox_uniform_layout.Init({ const_skybox });
		uniformbuffer_skybox.Init(device, skybox_uniform_layout);

		ShaderInfo::Load(PATH_SUFFIX BIN_SHADER_PATH "skybox.ts", skybox_shader);
		skybox_descriptor.Init(device, skybox_shader);
		skybox_descriptor.Bind(skyboxvertexbuffer);
		skybox_descriptor.Bind(cubemap_image.cubemap_texture, 0);
		skybox_descriptor.Bind(uniformbuffer_skybox, 4);
		skybox_pipeline.Init(device, skybox_descriptor, renderPass);

		descriptor.Bind(specular_ibl_image.texture, 40);
		descriptor.Bind(diffuse_convolution_image.cubemap_texture, 33);
		descriptor.Bind(shadowmap_image.cubemap_texture, 34);
		descriptor.Bind(shadowmap_image.cubemap_texture, 35);
		descriptor.Bind(shadowmap_image.cubemap_texture, 36);
		descriptor.Bind(shadowmap_image.cubemap_texture, 37);
		descriptor.Bind(shadowmap_image.cubemap_texture, 38);
		descriptor.Bind(specular_convolution_image.cubemap_texture, 39);
	}

	void GraphicsFramework::PreUpdate(GraphicRequiredData* i_data)
	{

	}

	void GraphicsFramework::Update(GraphicRequiredData* i_data)
	{
		uint32_t imageIndex;

		// Sync with GPU while get next image index of the target views
		{
			frameworkFence[currentFrame].Wait();
			imageIndex = swapChain.AcquireNextImage(imageDoneSemaphore[currentFrame]);
			frameworkFence[currentFrame].Reset();
		}

		// Issue commands
		{
			commandBuffers[currentFrame].ResetCommand();
			commandBuffers[currentFrame].BeginCommand();
			commandBuffers[currentFrame].BeginRenderPass(frameBuffers[imageIndex], renderPass);

			//{
			//	commandbuffers[current_frame].BindDescriptor(current_frame, skybox_descriptor, skybox_pipeline);
			//	Mat4f skybox_view_perspective_matrix = i_data->camera.perspective_matrix * Mat4f::TruncateToMat3(i_data->camera.view_matrix);
			//	uniformbuffer_skybox.Update(current_frame, static_cast<void*>(&skybox_view_perspective_matrix), sizeof(Mat4f), 0);
			//	commandbuffers[current_frame].Draw(skyboxvertexbuffer);
			//}

			commandBuffers[currentFrame].BindDescriptor(currentFrame, descriptor, pipeline);

			uniformbuffer_camera.Update(currentFrame, static_cast<void*>(&i_data->camera), sizeof(ConstantData::Camera), 0);
			uniformbuffer_light.Update(currentFrame, static_cast<void*>(&i_data->light), sizeof(ConstantData::Light), 0);
			if (i_data->model_data.Size() != 0)
			{
				i_data->model_data[0].model_view_perspective_matrix = i_data->camera.perspective_matrix * i_data->camera.view_matrix * i_data->model_data[0].model_position_matrix;
				uniformbuffer_model.Update(currentFrame, static_cast<void*>(&i_data->model_data[0]), sizeof(ConstantData::Model), 0);
			}

			commandBuffers[currentFrame].Draw(vertexbuffer);
			commandBuffers[currentFrame].Draw(vertexbuffer2);

			commandBuffers[currentFrame].EndRenderPass();
			commandBuffers[currentFrame].EndCommand();
		}

		device.SubmitToQueue(commandBuffers[currentFrame], &frameworkFence[currentFrame],
					  &imageDoneSemaphore[currentFrame], &presentableSemaphore[currentFrame]);

		device.Present(swapChain, imageIndex, presentableSemaphore[currentFrame]);

		currentFrame = 1 - currentFrame;
	}

	void GraphicsFramework::PostUpdate(GraphicRequiredData* i_data)
	{
		i_data->model_data.Clear();
		i_data->material_data.Clear();
	}

	void GraphicsFramework::ChangeViewportSize(uint32_t i_width, uint32_t i_height)
	{
	}
}

#endif // ENGINE_GRAPHIC_VULKAN