#pragma once
#include "Define.h"
#include "Device.h"

namespace Tempest
{
	class CommandBuffer
	{
	public:
		void Init(const Device& i_device);
		void CleanUp();

		VkCommandBuffer& GetBuffer(int index) const
		{
			DEBUG_ASSERT(index < buffer_count);
			return vk_commandbuffers[index];
		};

		const VkCommandPool& GetPool() const { return vk_commandpool; };

#ifdef ENGINE_GRAPHIC_VULKAN
	private:
		const Device* device;
		int buffer_count;
		VkCommandPool vk_commandpool;
		Array<VkCommandBuffer> vk_commandbuffers;
#endif // ENGINE_GRAPHIC_VULKAN

	};
}