#pragma once
#include "Define.h"
#include "Device.h"

namespace Tempest
{
	class CommandBuffer
	{
	public:
		void Initialize(Device& i_device);
		void Finalize();

		static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef ENGINE_GRAPHIC_VULKAN
		VkCommandPool commandpool;
		VkCommandBuffer commandbuffers[MAX_FRAMES_IN_FLIGHT];

	private:
		Device& device;				
#endif // ENGINE_GRAPHIC_VULKAN

	};
}