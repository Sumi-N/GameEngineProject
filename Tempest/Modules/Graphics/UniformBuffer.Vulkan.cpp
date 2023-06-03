#include "UniformBuffer.h"

#ifdef  ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	void UniformBuffer::Init(const Device& i_device, BufferLayout i_buffer_layout)
	{
		p_device = &i_device;
		layout = i_buffer_layout;

		// Create uniform buffer
		for (size_t i = 0; i < Graphics::BufferingCount; i++)
		{
			CreateBuffer(p_device->physical_device,
							p_device->logical_device,
							layout.stride,
							VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
							uniformbuffers[i],
							uniformbuffers_memories[i]);
		}
	}

	void UniformBuffer::CleanUp()
	{
		for (int i = 0; i < Graphics::BufferingCount; i++)
		{
			vkDestroyBuffer(p_device->logical_device, uniformbuffers[i], nullptr);
			vkFreeMemory(p_device->logical_device, uniformbuffers_memories[i], nullptr);
		}
	}

	void UniformBuffer::Update(int i_index, void* i_data, size_t i_size, size_t i_offset) const
	{
		void* memory_data;
		vkMapMemory(p_device->logical_device, uniformbuffers_memories[i_index], i_offset, i_size, 0, &memory_data);
		memcpy(memory_data, i_data, i_size);
		vkUnmapMemory(p_device->logical_device, uniformbuffers_memories[i_index]);
	}
}
#endif // ENGINE_GRAPHIC_VULKAN