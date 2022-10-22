#pragma once
#include "Define.h"
#include "Device.h"
#include "Buffer.h"

namespace Tempest
{
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer() = default;
		~VertexBuffer() = default;

		void Init(const Device& i_device,
				  BufferLayout i_buffer_layout,
				  const void* i_vertex_data,
				  uint32_t i_vertex_size,
				  const void * i_index_data,
				  uint32_t i_index_size);
		void CleanUp() const;

		uint32_t indecies_count;

	private:
		const Device* device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkBuffer vertexbuffer;
		VkBuffer indexbuffer;

	private:
		VkDeviceMemory vertexbuffer_memory;
		VkDeviceMemory indexbuffer_memory;

#endif // ENGINE_GRAPHIC_VULKAN
	};
}