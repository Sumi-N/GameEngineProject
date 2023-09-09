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
				  const Descriptor& i_descriptor,
				  const RenderPass& i_renderpass);
		void CleanUp();

	private:
		const Device* p_device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkPipelineLayout pipeline_layout;
		VkPipeline pipeline;

	private:

#endif

	};
}
