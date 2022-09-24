#include "CommandBuffer.h"

#ifdef ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	void CommandBuffer::Init(const Device& i_device)
	{
		device = &i_device;

		VkCommandBufferAllocateInfo commandbuffer_allocate_info{};
		commandbuffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandbuffer_allocate_info.commandPool = device->commandpool;
		commandbuffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandbuffer_allocate_info.commandBufferCount = 1;

		VkResult create_commandbuffer_result = vkAllocateCommandBuffers(device->logical_device, &commandbuffer_allocate_info, &commandbuffer);
		DEBUG_ASSERT(create_commandbuffer_result == VK_SUCCESS);
	}

	void CommandBuffer::CleanUp()
	{
	}
}
#endif // ENGINE_GRAPHIC_VULKAN
