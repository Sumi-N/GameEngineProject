#pragma once
#include "Define.h"

namespace Tempest
{
	class Device
	{
	public:
		static void Initialize(Array<const char*> i_extensions);
		static void Finalize();

#ifdef ENGINE_GRAPHIC_VULKAN
		VkPhysicalDevice physical_device;
		VkDevice logical_device;
		VkInstance instance;
		VkDebugUtilsMessengerEXT debug_layer;
#endif
	};
}