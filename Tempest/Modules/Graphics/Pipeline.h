#pragma once

#include "Define.h"
#include "Device.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "UniformBuffer.h"

namespace Tempest
{
	class Pipeline
	{
	public:

		void Init(const Device&, const SwapChain&, const Shader&, const VertexBuffer&, const UniformBuffer&);
		void CleanUp();

#ifdef ENGINE_GRAPHIC_VULKAN
		VkRenderPass render_pass;
		VkPipelineLayout pipeline_layout;
		VkPipeline graphics_pipeline;

	private:
		const Device* device;
#endif

	};
}
