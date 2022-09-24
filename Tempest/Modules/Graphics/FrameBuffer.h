#pragma once
#include "Define.h"
#include "Device.h"
#include "SwapChain.h"
#include "Texture.h"
#include "RenderPass.h"

namespace Tempest
{
	// The number of enum also represents the texture unit number
	enum class FrameType : uint8_t
	{
		ShadowCubeMap = 0,
		EquirectangularMap = 1,
		IrradianceMap = 2,
		Specular = 3,
		BRDF = 4,
		Image = 5,
		ShadowMap = 6,

		UnInitialized = 255,
	};

	class FrameBuffer
	{
	public:
		FrameBuffer() = default;
		~FrameBuffer() = default;

		void Init(const Device& i_device, const RenderPass& i_render_pass, const SwapChain& i_swapchain, int index);
		void Init(const Device& i_device, const RenderPass& i_render_pass, const Texture& i_texture);
		void CleanUp() const;

		uint32_t width;
		uint32_t height;

	public:
		const Device* device;
		const RenderPass* render_pass;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		const VkFramebuffer& GetBuffer() const { return framebuffer; }

	private:
		VkFramebuffer framebuffer{};

#endif // ENGINE_GRAPHIC_VULKAN
	};
}