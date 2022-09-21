#include "VertexBuffer.h"

namespace Tempest
{
#ifdef ENGINE_GRAPHIC_VULKAN

	namespace
	{
		uint32_t FindMemoryType(VkPhysicalDevice physical_device, uint32_t type_filter, VkMemoryPropertyFlags properties)
		{

			VkPhysicalDeviceMemoryProperties memory_properties;
			vkGetPhysicalDeviceMemoryProperties(physical_device, &memory_properties);

			for (uint32_t i = 0; i < memory_properties.memoryTypeCount; i++)
			{
				if ((type_filter & (1 << i)) && (memory_properties.memoryTypes[i].propertyFlags & properties) == properties)
				{
					return i;
				}
			}

			DEBUG_ASSERT(false);
			return 0;
		}

		void CreateBuffer(VkPhysicalDevice physical_device, VkDevice logical_device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory)
		{
			VkBufferCreateInfo bufferInfo{};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = size;
			bufferInfo.usage = usage;
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			auto create_result = vkCreateBuffer(logical_device, &bufferInfo, nullptr, &buffer);
			DEBUG_ASSERT(create_result == VK_SUCCESS);

			VkMemoryRequirements memory_requirements;
			vkGetBufferMemoryRequirements(logical_device, buffer, &memory_requirements);

			VkMemoryAllocateInfo alloc_info{};
			alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			alloc_info.allocationSize = memory_requirements.size;
			alloc_info.memoryTypeIndex = FindMemoryType(physical_device, memory_requirements.memoryTypeBits, properties);

			auto allocate_result = vkAllocateMemory(logical_device, &alloc_info, nullptr, &buffer_memory);
			DEBUG_ASSERT(allocate_result == VK_SUCCESS);

			vkBindBufferMemory(logical_device, buffer, buffer_memory, 0);
		}
	}

	void VertexBuffer::Init(const Device& i_device, const Shader& i_shader)
	{
		device = &i_device;
		stride = static_cast<uint32_t>(i_shader.vertex_stride);

		binding_description.binding = 0;
		binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		//binding_description.stride = static_cast<uint32_t>(i_shader.vertex_stride);
		binding_description.stride = 14 * 4;

		attribute_descriptions.Resize(i_shader.vertex_info.Size());
		for (int i = 0; i < attribute_descriptions.Size(); i++)
		{
			attribute_descriptions[i].binding = i_shader.vertex_info[i].binding;
			attribute_descriptions[i].location = i_shader.vertex_info[i].location;
			attribute_descriptions[i].format = static_cast<VkFormat>(i_shader.vertex_info[i].format);
			attribute_descriptions[i].offset = i_shader.vertex_info[i].offset;
		}
	}

	void VertexBuffer::InitData(const CommandBuffer& i_commandbuffer, const void* i_vertex_data, uint32_t i_vertex_size, const void* i_index_data, uint32_t i_index_size)
	{
		index_coount = i_index_size / sizeof(uint32_t);

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
				auto vk_commandbuffer = i_commandbuffer.GetBuffer(0);

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

				VkQueue graphics_queue;
				vkGetDeviceQueue(device->logical_device, device->queue_family_indices.graphics_family.value(), 0, &graphics_queue);
				vkQueueSubmit(graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
				vkQueueWaitIdle(graphics_queue);
			}

			vkDestroyBuffer(device->logical_device, stagingbuffer, nullptr);
			vkFreeMemory(device->logical_device, stagingbuffer_memory, nullptr);
		}

		// Index buffer
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
				auto vk_commandbuffer = i_commandbuffer.GetBuffer(0);

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

				VkQueue graphics_queue;
				vkGetDeviceQueue(device->logical_device, device->queue_family_indices.graphics_family.value(), 0, &graphics_queue);
				vkQueueSubmit(graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
				vkQueueWaitIdle(graphics_queue);
			}

			vkDestroyBuffer(device->logical_device, stagingbuffer, nullptr);
			vkFreeMemory(device->logical_device, stagingbuffer_memory, nullptr);
		}
	}

	void VertexBuffer::CleanUp() const
	{
	}

	void VertexBuffer::CleanUpData() const
	{
		vkDestroyBuffer(device->logical_device, vertexbuffer, nullptr);
		vkFreeMemory(device->logical_device, vertexbuffer_memory, nullptr);

		vkDestroyBuffer(device->logical_device, indexbuffer, nullptr);
		vkFreeMemory(device->logical_device, indexbuffer_memory, nullptr);
	}

#endif // ENGINE_GRAPHIC_OPENGL

}
