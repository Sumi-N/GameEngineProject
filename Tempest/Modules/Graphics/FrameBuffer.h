#pragma once
#include "Define.h"
#include "Device.h"
#include "SwapChain.h"
#include "Texture.h"
#include "RenderPass.h"

namespace Tempest
{
	class FrameBuffer
	{
	public:
		FrameBuffer() = default;
		~FrameBuffer() = default;

		void Init(const Device& i_device, const RenderPass& i_render_pass, const SwapChain& i_swapchain, uint32_t index);
		void Init(const Device& i_device, const RenderPass& i_render_pass, const Texture& i_texture, uint32_t i_miplevel = 0);
		void CleanUp() const;

		uint32_t width;
		uint32_t height;

	public:
		const Device* p_device;
		const RenderPass* p_render_pass;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkFramebuffer framebuffer{};

	private:

#endif // ENGINE_GRAPHIC_VULKAN
	};
}