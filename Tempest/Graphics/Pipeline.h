#pragma once

#include "Define.h"
#include "Device.h"
#include "SwapChain.h"

namespace Tempest
{
	class Pipeline
	{
	public:

		void Initialize(const Device& i_device, const SwapChain& i_swapchain, const Array<Resource::Shader>& shaders);

#ifdef ENGINE_GRAPHIC_VULKAN
		VkRenderPass render_pass;
		VkShaderModule shader_module[5];
		VkPipelineLayout pipeline_layout;
		VkPipeline graphics_pipeline;
#endif

	};
}
