#pragma once
#include "Define.h"
#include "Window.h"

namespace Tempest
{
	class Device
	{
	public:
		void Init(Window* i_window);
		void CleanUp();

		static constexpr int graphics_buffering_count = GRAPHICS_BUFFERING_COUNT;
		int min_uniform_buffer_offset_alignment;

#ifdef ENGINE_GRAPHIC_VULKAN
		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphics_family;
			std::optional<uint32_t> present_family;
		} queue_family_indices;

		VkPhysicalDeviceProperties device_properties;
		VkPhysicalDeviceFeatures device_features;
		Array<const char*> device_extensions;
		Array<VkExtensionProperties> availableExtensions{};

		VkInstance instance;
		VkDebugUtilsMessengerEXT debug_messenger;
		VkPhysicalDevice physical_device;
		VkDevice logical_device;
		VkSurfaceKHR surface;
#endif
	};
}