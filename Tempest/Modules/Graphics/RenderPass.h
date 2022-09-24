#pragma once
#include "Define.h"
#include "Device.h"
#include "SwapChain.h"
#include "Texture.h"

namespace Tempest
{
	class RenderPass
	{
	public:
		RenderPass() = default;
		~RenderPass() = default;

		void Init(const Device& i_device, const SwapChain& i_swapchain);
		void Init(const Device& i_device, const Texture& i_texture);
		void CleanUp();

	private:
		const Device* device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkRenderPass render_pass;

	private:

#endif // ENGINE_GRAPHIC_VULKAN
	};
}
