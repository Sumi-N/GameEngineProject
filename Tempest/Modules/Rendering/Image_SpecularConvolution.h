#pragma once
#include "Define.h"
#include "PrimitiveDrawer.h"

namespace Tempest
{
	class SpecularConvolutionImage
	{
	public:
		void Init(const Device& i_device, const Texture& i_cubemap_texture)
		{
			Shader::Load(PATH_SUFFIX BIN_SHADER_PATH "cubemap_specular_convolution.ts", shader);

			TextureInfo cubemap_texture_info{};
			{
				cubemap_texture_info.width = 512;
				cubemap_texture_info.height = 512;
				cubemap_texture_info.count = 6;
				cubemap_texture_info.mip_count = 5;
				cubemap_texture_info.need_samper = true;
				cubemap_texture_info.has_data = false;
				cubemap_texture_info.format = TextureFormat::R16G16B16A16_SFLOAT;
				cubemap_texture_info.usage_flag = USAGE_COLOR_ATTACHMENT_BIT | USAGE_SAMPLED_BIT;
				cubemap_texture_info.aspect_flag = COLOR_BIT_ASPECT;
#ifdef  ENGINE_GRAPHIC_VULKAN
				cubemap_texture_info.additional_flag = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
#else
#error
#endif //ENGINE_GRAPHIC_VULKAN
			}
			cubemap_texture.Init(i_device, cubemap_texture_info);

			// Create uniform date for 6 directions of the cube map
			{
				Mat4f view[6];
				Mat4f projection = Mat4f::Perspective(90, 1, Graphics::NearClip, Graphics::FarClip);

				view[0] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(1, 0, 0), Vec3f(0, -1, 0));
				view[1] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(-1, 0, 0), Vec3f(0, -1, 0));
				view[2] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, 1, 0), Vec3f(0, 0, 1));
				view[3] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, -1, 0), Vec3f(0, 0, -1));
				view[4] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, 0, 1), Vec3f(0, -1, 0));
				view[5] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, 0, -1), Vec3f(0, -1, 0));

				for (int i = 0; i < 6; i++)
				{
					projection_matrxs[i] = projection * view[i];
				}

				BufferUnit const_shadow1{ BufferFormat::Mat4, "view_perspective_matrix0" };
				BufferUnit const_shadow2{ BufferFormat::Mat4, "view_perspective_matrix1" };
				BufferUnit const_shadow3{ BufferFormat::Mat4, "view_perspective_matrix2" };
				BufferUnit const_shadow4{ BufferFormat::Mat4, "view_perspective_matrix3" };
				BufferUnit const_shadow5{ BufferFormat::Mat4, "view_perspective_matrix4" };
				BufferUnit const_shadow6{ BufferFormat::Mat4, "view_perspective_matrix5" };
				BufferUnit const_shadow7{ BufferFormat::Float4, "position" };
				BufferLayout cubemap_uniform_layout;
				cubemap_uniform_layout.Init({ const_shadow1, const_shadow2, const_shadow3, const_shadow4, const_shadow5, const_shadow6, const_shadow7 });
				cubemap_uniform.Init(i_device, cubemap_uniform_layout);
				cubemap_uniform.Update(0, projection_matrxs, sizeof(Mat4f) * 6, 0);
			}

			{
				BufferUnit const_roughness{ BufferFormat::Float, "roughness" };
				BufferLayout roughness_uniform_layout;
				roughness_uniform_layout.Init({const_roughness});
				roughness_uniform.Init(i_device, roughness_uniform_layout);
			}

			renderpass.Init(i_device, cubemap_texture);
			for (int i = 0; i < 5; i++)
			{
				framebuffers[i].Init(i_device, renderpass, cubemap_texture, i);
			}
			descriptor.Init(i_device, shader);
			descriptor.Bind(PrimitiveDrawer::VertexBufferCube);
			descriptor.Bind(roughness_uniform, 1);
			descriptor.Bind(cubemap_uniform, 5);
			descriptor.Bind(i_cubemap_texture, 0);
			pipeline.Init(i_device, shader, descriptor, renderpass);
		}

		void BeginRenderPass(const CommandBuffer& i_commandbuffer, uint32_t i_frame_index)
		{
			i_commandbuffer.BeginRenderPass(framebuffers[i_frame_index], renderpass);
		}

		void BindDescriptor(const CommandBuffer& i_commandbuffer)
		{
			i_commandbuffer.BindDescriptor(0, descriptor, pipeline);
		}

		void CleanUp()
		{

		}

	public:
		Texture cubemap_texture;
		UniformBuffer cubemap_uniform;
		UniformBuffer roughness_uniform;

		Pipeline pipeline;
		Shader shader;
		RenderPass renderpass;
		FrameBuffer framebuffers[5];
		Descriptor descriptor;

		Mat4f projection_matrxs[6];
	};
}