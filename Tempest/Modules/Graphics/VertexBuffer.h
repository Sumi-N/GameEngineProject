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
		void InitData(const void*, uint32_t, const void*, uint32_t);
		void CleanUp() const;
		void CleanUpData() const;

		uint32_t GetStride() const { return stride; };

	public:
		uint32_t stride;
		uint32_t index_coount;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkVertexInputBindingDescription binding_description;
		Array<VkVertexInputAttributeDescription> attribute_descriptions;

		VkBuffer vertexbuffer;
		VkDeviceMemory vertexbuffer_memory;

		VkBuffer indexbuffer;
		VkDeviceMemory indexbuffer_memory;
	private:
		const Device* device;
#endif // ENGINE_GRAPHIC_VULKAN
	};
}