#include "Queue.h"

#ifdef ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	void Queue::Init(const Device& device)
	{
		vkGetDeviceQueue(device.logical_device, device.queue_family_indices.graphics_family.value(), 0, &graphics_queue);
		vkGetDeviceQueue(device.logical_device, device.queue_family_indices.present_family.value(), 0, &present_queue);
	}

	void Queue::Cleanup()
	{

	}
}
#endif