#pragma once
#include "Define.h"
#include "Device.h"
#include "RenderPass.h"
#include "Descriptor.h"

namespace Tempest
{
	class Pipeline
	{
	public:
		Pipeline() = default;
		~Pipeline() = default;

		void Init(const Device& i_device,
				  const Shader& i_shader,
				  const Descriptor& i_descriptor,
				  const RenderPass& i_renderpass,
				  uint32_t vertex_stride);
		void CleanUp();

	private:
		const Device* device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkPipelineLayout pipeline_layout;
		VkPipeline pipeline;

	private:

#endif

	};
}
