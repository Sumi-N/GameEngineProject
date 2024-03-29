#pragma once
#include "PrimitiveDrawer.h"

namespace Tempest
{
	class SpecularIBLImage
	{
	public:
		void Init(const Device& i_device)
		{
			ShaderInfo::Load(PATH_SUFFIX BIN_SHADER_PATH "specular_ibl.ts", shader);
			TextureInfo texture_info{};
			{
				texture_info.width = 512;
				texture_info.height = 512;
				texture_info.count = 1;
				texture_info.mip_count = 1;
				texture_info.need_samper = true;
				texture_info.has_data = false;
				texture_info.format = TextureFormat::R16G16_SFLOAT;
				texture_info.usage_flag = USAGE_COLOR_ATTACHMENT_BIT | USAGE_SAMPLED_BIT;
				texture_info.aspect_flag = COLOR_BIT_ASPECT;
			}
			texture.Init(i_device, texture_info);
			renderpass.Init(i_device, texture);
			framebuffer.Init(i_device, renderpass, texture);
			descriptor.Bind(PrimitiveDrawer::VertexBufferQuad);
			descriptor.Init(i_device, shader);
			pipeline.Init(i_device, descriptor, renderpass);
		}

		void BeginRenderPass(const CommandBuffer& i_commandbuffer)
		{
			i_commandbuffer.BeginRenderPass(framebuffer, renderpass);
		}

		void BindDescriptor(const CommandBuffer& i_commandbuffer)
		{
			i_commandbuffer.BindDescriptor(0, descriptor, pipeline);
		}

		void CleanUp()
		{

		}

	public:
		Pipeline pipeline;
		ShaderInfo shader;
		Texture texture;
		RenderPass renderpass;
		FrameBuffer framebuffer;
		Descriptor descriptor;
	};
}