#pragma once

#include "Define.h"
#include "Device.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "UniformBuffer.h"
#include "RenderPass.h"

namespace Tempest
{
	class Pipeline
	{
	public:

		void Init(const Device&, const SwapChain&, const Shader&, const VertexBuffer&, const UniformBuffer&, const RenderPass&);
		void CleanUp();

	private:
		const Device* device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		const VkPipelineLayout& GetPipelineLayout() { return pipeline_layout; }
		const VkPipeline& GetPipeline() { return graphics_pipeline; }
	private:
		VkPipelineLayout pipeline_layout;
		VkPipeline graphics_pipeline;
#endif

	};
}
