#include "CommandBuffer.h"

#ifdef ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	void CommandBuffer::Init(const Device& i_device)
	{
		device = &i_device;
		buffer_count = device->graphics_buffering_count;
		vk_commandbuffers.Resize(buffer_count);

		// Create CommandPool
		{
			VkCommandPoolCreateInfo pool_create_info{};
			pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			pool_create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
			pool_create_info.queueFamilyIndex = device->queue_family_indices.graphics_family.value();

			VkResult create_commandpool_result = vkCreateCommandPool(device->logical_device, &pool_create_info, nullptr, &vk_commandpool);
			DEBUG_ASSERT(create_commandpool_result == VK_SUCCESS);

			VkCommandBufferAllocateInfo commandbuffer_allocate_info{};
			commandbuffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			commandbuffer_allocate_info.commandPool = vk_commandpool;
			commandbuffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			commandbuffer_allocate_info.commandBufferCount = buffer_count;

			VkResult create_commandbuffer_result = vkAllocateCommandBuffers(device->logical_device, &commandbuffer_allocate_info, vk_commandbuffers.Data());
			DEBUG_ASSERT(create_commandbuffer_result == VK_SUCCESS);
		}
	}

	void CommandBuffer::CleanUp()
	{
		vkDestroyCommandPool(device->logical_device, vk_commandpool, nullptr);
	}
}
#endif // ENGINE_GRAPHIC_VULKAN
