#pragma once
#include "Define.h"
#include "Device.h"

namespace Tempest
{
	class Queue
	{
	public:
		void Initialize(const Device& i_device);
		void Finalize();

#ifdef ENGINE_GRAPHIC_VULKAN
		VkQueue graphics_queue;
		VkQueue present_queue;
#endif
	};
}