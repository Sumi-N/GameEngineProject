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

		static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef ENGINE_GRAPHIC_VULKAN
		VkCommandPool commandpool;
		VkCommandBuffer commandbuffers[MAX_FRAMES_IN_FLIGHT];

	private:
		const Device* device;
#endif // ENGINE_GRAPHIC_VULKAN

	};
}