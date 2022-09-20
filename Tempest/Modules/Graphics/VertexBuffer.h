#pragma once
#include "Define.h"
#include "Device.h"
#include "CommandBuffer.h"

namespace Tempest
{
	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		~VertexBuffer() = default;

		void Init(const Device&, const Shader&);
		void InitData(const CommandBuffer&, const void*, uint32_t, const void*, uint32_t);
		void CleanUp() const;
		void CleanUpData() const;

		uint32_t GetStride() const { return stride; };

	private:
		uint32_t stride;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkVertexInputBindingDescription binding_description;
		Array<VkVertexInputAttributeDescription> attribute_descriptions;

	private:
		const Device* device;
		VkBuffer vertexbuffer;
		VkDeviceMemory vertexbuffer_memory;

		VkBuffer indexbuffer;
		VkDeviceMemory indexbuffer_memory;
#endif // ENGINE_GRAPHIC_VULKAN
	};
}