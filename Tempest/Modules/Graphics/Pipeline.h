#pragma once
#include "Define.h"
#include "Device.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "RenderPass.h"
#include "Descriptor.h"

namespace Tempest
{
	class Pipeline
	{
	public:
		Pipeline() = default;
		~Pipeline() = default;

		void Init(const Device&, const SwapChain&, const Shader&, const VertexBuffer&, const Descriptor&, const RenderPass&);
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
