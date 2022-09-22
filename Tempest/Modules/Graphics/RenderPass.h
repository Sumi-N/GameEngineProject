#pragma once
#include "Define.h"
#include "Device.h"
#include "SwapChain.h"

namespace Tempest
{
	class RenderPass
	{
	public:
		RenderPass() = default;
		~RenderPass() = default;

		void Init(const Device& i_device, const SwapChain& i_swapchain);
		void CleanUp();

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		const VkRenderPass& GetRenderPass() const { return render_pass; }

	private:
		const Device* device;
		VkRenderPass render_pass{};
#endif // ENGINE_GRAPHIC_VULKAN
	};
}
