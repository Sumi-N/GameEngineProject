#pragma once
#include "Define.h"
#include "Device.h"
#include "Buffer.h"

namespace Tempest
{
	class UniformBuffer : public Buffer
	{
	public:
		UniformBuffer()  = default;
		~UniformBuffer() = default;

		void Init(const Device& i_device, BufferLayout i_buffer_layout);
		void CleanUp();

		void Update(int i_index, void* i_data, size_t i_size, size_t i_offset) const;

	private:
		const Device* p_device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkBuffer       uniformbuffers[Graphics::BufferingCount];

	private:
		VkDeviceMemory uniformbuffers_memories[Graphics::BufferingCount];

#endif // ENGINE_GRAPHIC_VULKAN
	};
}