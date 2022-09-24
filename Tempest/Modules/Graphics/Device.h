#pragma once
#include "Define.h"
#include "Window.h"

namespace Tempest
{
	class Device
	{
	public:
		Device() = default;
		~Device() = default;

		void Init(Window* i_window);
		void CleanUp();

		int   min_buffer_offset_alignment;
		float max_sampler_anisotropy;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkInstance        instance;
		VkPhysicalDevice  physical_device;
		VkDevice          logical_device;
		VkSurfaceKHR      surface;

		VkQueue           queue;
		uint32_t          queue_family_index;

		VkCommandPool     commandpool;
		VkCommandBuffer   system_commandbuffer;

	private:
		VkDebugUtilsMessengerEXT debug_messenger;
#endif
	};
}