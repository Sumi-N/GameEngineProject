#pragma once
#include "Define.h"
#include "Shader.h"
#include "Device.h"
#include "SwapChain.h"
#include "Pipeline.h"
#include "DrawPrimitives.h"

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

		FrameType frametype = FrameType::UnInitialized;
		Shader    shader;
		int       unit_number = -1;
		int       width = 0, height = 0;

		void Init(const Device& i_Device, const SwapChain& i_swapchain, const Pipeline& i_pipeline);
		void CleanUp();
		void Init(FrameType i_type, int i_unitnum, int i_width, int i_height);
		void Recreate(int i_width, int i_height);
		void BindFrame();
		void BindTextureUnit();
		void RenderOnce();

#ifdef ENGINE_GRAPHIC_OPENGL

		uint32_t GetBufferID() const;
		uint32_t GetColorID() const;
		uint32_t GetDepthID() const;

		GLuint  bufferid = 0;

		GLuint  textureid_color = 0;
		GLuint  textureid_depth = 0;

#else ENGINE_GRAPHIC_VULKAN

		Tempest::Array<VkFramebuffer> framebuffers;

	private:
		const Device* device;
#endif // ENGINE_GRAPHIC_OPENGL

	};
}