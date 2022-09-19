#pragma once
#include "Define.h"
#include "Device.h"

namespace Tempest
{
	class Queue
	{
	public:
		void Init(const Device& i_device);
		void Cleanup();

#ifdef ENGINE_GRAPHIC_VULKAN
		VkQueue graphics_queue;
		VkQueue present_queue;
#endif
	};
}