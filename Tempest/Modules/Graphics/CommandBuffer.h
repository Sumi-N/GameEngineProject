#pragma once
#include "Define.h"
#include "Device.h"
#include "RenderPass.h"
#include "FrameBuffer.h"
#include "Pipeline.h"
#include "Descriptor.h"
#include "VertexBuffer.h"

namespace Tempest
{
	class CommandBuffer
	{
	public:
		CommandBuffer() = default;
		~CommandBuffer() = default;

		void Init(const Device& i_device);
		void CleanUp();

		void BeginCommand() const;
		void BindFrameBuffer(const FrameBuffer& i_framebuffer, const RenderPass& i_renderpass) const;
		void BindDescriptor(int i_index, const Descriptor& i_descriptor, const Pipeline& i_pipeline) const;
		void Draw(const VertexBuffer& i_vertexbuffer) const;
		void EndCommand() const;
		void Submit() const;

	private:
		const Device* device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkCommandBuffer commandbuffer;

	private:

#endif // ENGINE_GRAPHIC_VULKAN
	};
}