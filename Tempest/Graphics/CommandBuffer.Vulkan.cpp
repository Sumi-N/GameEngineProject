#include "CommandBuffer.h"

#ifdef ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	void CommandBuffer::Initialize(Device& i_device)
	{
		device = &i_device;

		// Create CommandPool
		{
			VkCommandPoolCreateInfo pool_create_info{};
			pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			pool_create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
			pool_create_info.queueFamilyIndex = device->queue_family_indices.graphics_family.value();

			VkResult create_commandpool_result = vkCreateCommandPool(device->logical_device, &pool_create_info, nullptr, &commandpool);
			DEBUG_ASSERT(create_commandpool_result == VK_SUCCESS);

			VkCommandBufferAllocateInfo commandbuffer_allocate_info{};
			commandbuffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			commandbuffer_allocate_info.commandPool = commandpool;
			commandbuffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			commandbuffer_allocate_info.commandBufferCount = MAX_FRAMES_IN_FLIGHT;

			VkResult create_commandbuffer_result = vkAllocateCommandBuffers(device->logical_device, &commandbuffer_allocate_info, commandbuffers);
			DEBUG_ASSERT(create_commandbuffer_result == VK_SUCCESS);
		}
	}

	void CommandBuffer::Finalize()
	{

	}
}
#endif // ENGINE_GRAPHIC_VULKAN
