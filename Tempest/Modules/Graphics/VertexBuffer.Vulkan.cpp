#include "VertexBuffer.h"

#ifdef ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	void VertexBuffer::Init(const Device& i_device,
							BufferLayout i_buffer_layout,
							const void* i_vertex_data,
							size_t i_vertex_size,
							const void* i_index_data,
							size_t i_index_size)
	{
		device = &i_device;
		layout = i_buffer_layout;
		indecies_count = i_index_size / sizeof(uint32_t);

		// Vertex attribute
		{
			VkBuffer stagingbuffer;
			VkDeviceMemory stagingbuffer_memory;
			CreateBuffer(device->physical_device,
						 device->logical_device,
						 i_vertex_size,
						 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
						 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
						 stagingbuffer,
						 stagingbuffer_memory);

			void* data;
			vkMapMemory(device->logical_device, stagingbuffer_memory, 0, i_vertex_size, 0, &data);
			memcpy(data, i_vertex_data, i_vertex_size);
			vkUnmapMemory(device->logical_device, stagingbuffer_memory);

			CreateBuffer(device->physical_device,
						 device->logical_device,
						 i_vertex_size,
						 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
						 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
						 vertexbuffer,
						 vertexbuffer_memory);

			// Copy buffer
			{
				auto vk_commandbuffer = device->system_commandbuffer;

				VkCommandBufferBeginInfo begin_info{};
				begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

				auto begin_result = vkBeginCommandBuffer(vk_commandbuffer, &begin_info);
				DEBUG_ASSERT(begin_result == VK_SUCCESS);

				VkBufferCopy copy_region{};
				copy_region.srcOffset = 0;
				copy_region.dstOffset = 0;
				copy_region.size = i_vertex_size;
				vkCmdCopyBuffer(vk_commandbuffer, stagingbuffer, vertexbuffer, 1, &copy_region);

				auto end_result = vkEndCommandBuffer(vk_commandbuffer);
				DEBUG_ASSERT(end_result == VK_SUCCESS);

				VkSubmitInfo submit_info{};
				submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
				submit_info.commandBufferCount = 1;
				submit_info.pCommandBuffers = &vk_commandbuffer;

				vkQueueSubmit(device->queue, 1, &submit_info, VK_NULL_HANDLE);
				vkQueueWaitIdle(device->queue);
			}

			vkDestroyBuffer(device->logical_device, stagingbuffer, nullptr);
			vkFreeMemory(device->logical_device, stagingbuffer_memory, nullptr);
		}

		// Index buffer
		if(i_index_data)
		{
			VkBuffer stagingbuffer;
			VkDeviceMemory stagingbuffer_memory;
			CreateBuffer(device->physical_device,
						 device->logical_device,
						 i_index_size,
						 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
						 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
						 stagingbuffer,
						 stagingbuffer_memory);

			void* data;
			vkMapMemory(device->logical_device, stagingbuffer_memory, 0, i_index_size, 0, &data);
			memcpy(data, i_index_data, i_index_size);
			vkUnmapMemory(device->logical_device, stagingbuffer_memory);

			CreateBuffer(device->physical_device,
						 device->logical_device,
						 i_index_size,
						 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
						 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
						 indexbuffer,
						 indexbuffer_memory);

			// Copy buffer
			{
				auto vk_commandbuffer = device->system_commandbuffer;

				VkCommandBufferBeginInfo begin_info{};
				begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

				vkBeginCommandBuffer(vk_commandbuffer, &begin_info);

				VkBufferCopy copy_region{};
				copy_region.size = i_index_size;
				vkCmdCopyBuffer(vk_commandbuffer, stagingbuffer, indexbuffer, 1, &copy_region);

				vkEndCommandBuffer(vk_commandbuffer);

				VkSubmitInfo submit_info{};
				submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
				submit_info.commandBufferCount = 1;
				submit_info.pCommandBuffers = &vk_commandbuffer;

				vkQueueSubmit(device->queue, 1, &submit_info, VK_NULL_HANDLE);
				vkQueueWaitIdle(device->queue);
			}

			vkDestroyBuffer(device->logical_device, stagingbuffer, nullptr);
			vkFreeMemory(device->logical_device, stagingbuffer_memory, nullptr);
		}
	}

	void VertexBuffer::CleanUp() const
	{
		vkDestroyBuffer(device->logical_device, vertexbuffer, nullptr);
		vkFreeMemory(device->logical_device, vertexbuffer_memory, nullptr);

		vkDestroyBuffer(device->logical_device, indexbuffer, nullptr);
		vkFreeMemory(device->logical_device, indexbuffer_memory, nullptr);
	}
}
#endif // ENGINE_GRAPHIC_VULKAN
