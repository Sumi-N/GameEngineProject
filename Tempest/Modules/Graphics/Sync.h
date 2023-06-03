#pragma once
#include "Device.h"

namespace Tempest
{
	class Fence
	{
	public:
		void Init(const Device& i_device)
		{
			p_device = &i_device;
			VkFenceCreateInfo fenceInfo{};
			fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

			auto result = vkCreateFence(p_device->logical_device, &fenceInfo, nullptr, &fence);
			DEBUG_ASSERT(result == VK_SUCCESS);
		}

		void Wait()
		{
			vkWaitForFences(p_device->logical_device, 1, &fence, VK_TRUE, UINT64_MAX);
		}

		void Reset()
		{
			vkResetFences(p_device->logical_device, 1, &fence);
		}
	private:
		const Device* p_device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkFence fence;

	private:

#endif // ENGINE_GRAPHIC_VULKAN
	};

	class Semaphore
	{
	public:
		void Init(const Device& i_device)
		{
			p_device = &i_device;
			VkSemaphoreCreateInfo semaphoreInfo{};
			semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			auto result = vkCreateSemaphore(p_device->logical_device, &semaphoreInfo, nullptr, &semaphore);
			DEBUG_ASSERT(result == VK_SUCCESS);
		}

	private:
		const Device* p_device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkSemaphore semaphore;

	private:

#endif // ENGINE_GRAPHIC_VULKAN
	};
}