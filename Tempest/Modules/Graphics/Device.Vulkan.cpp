#include "Device.h"

#ifdef ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	namespace
	{
		bool CheckValidationLayerSupport(const char* layer_name)
		{
			uint32_t layer_count;
			vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

			Tempest::Array<VkLayerProperties> available_layers;
			available_layers.Resize(layer_count);
			vkEnumerateInstanceLayerProperties(&layer_count, available_layers.Data());


			for (const auto& layer_properties : available_layers)
			{
				if (strcmp(layer_name, layer_properties.layerName) == 0)
				{
					return true;
				}
			}

			return false;
		}

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
			VkDebugUtilsMessageTypeFlagsEXT message_type,
			const VkDebugUtilsMessengerCallbackDataEXT* pcallback_data,
			void* puser_data)
		{

			std::cerr << "validation layer: " << pcallback_data->pMessage << std::endl;

			return VK_FALSE;
		}

		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pcreate_info, const VkAllocationCallbacks* pallocator, VkDebugUtilsMessengerEXT* pdebug_messenger)
		{
			auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
			if (func != nullptr)
			{
				return func(instance, pcreate_info, pallocator, pdebug_messenger);
			}
			else
			{
				return VK_ERROR_EXTENSION_NOT_PRESENT;
			}
		}

		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger, const VkAllocationCallbacks* pallocator)
		{
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
			if (func != nullptr)
			{
				func(instance, debug_messenger, pallocator);
			}
		}
	}

	void Device::Init(Window* i_window)
	{
		// Initialize instance
		{
			VkApplicationInfo app_info{};
			app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			app_info.pApplicationName = "Tempest";
			app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			app_info.pEngineName = nullptr;
			app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			app_info.apiVersion = VK_API_VERSION_1_2;

			Array<const char*> extensions = i_window->GetRequiredExtensions();

			VkInstanceCreateInfo instance_create_info{};
			instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instance_create_info.pApplicationInfo = &app_info;
			instance_create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.Size());
			instance_create_info.ppEnabledExtensionNames = extensions.Data();

#ifdef ENABLE_VULKAN_VALIDATION_LAYERS
			const char* layer_names = "VK_LAYER_KHRONOS_validation";
			instance_create_info.enabledLayerCount = 1;
			instance_create_info.ppEnabledLayerNames = &layer_names;

			if (!CheckValidationLayerSupport(layer_names))
			{
				DEBUG_ASSERT_WITHMESSAGE(false, "There is a chance that you haven't installed Vulkan SDK");
			}
#else
		instance_create_info.enabledLayerCount = 0;
		instance_create_info.pNext = nullptr;
#endif // ENABLE_VULKAN_VALIDATION_LAYERS

			// The second argument is for custom allocator, might need to change it later
			VkResult create_instance_result = vkCreateInstance(&instance_create_info, nullptr, &instance);
			DEBUG_ASSERT(create_instance_result == VK_SUCCESS);

		// Setup debug layer
#ifdef ENABLE_VULKAN_VALIDATION_LAYERS
			VkDebugUtilsMessengerCreateInfoEXT debug_util_messenger_create_info = {};
			debug_util_messenger_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			debug_util_messenger_create_info.messageSeverity =
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			debug_util_messenger_create_info.messageType =
				//VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			debug_util_messenger_create_info.pfnUserCallback = (PFN_vkDebugUtilsMessengerCallbackEXT)DebugCallback;
			debug_util_messenger_create_info.pUserData = nullptr;

			VkResult create_debug_result = CreateDebugUtilsMessengerEXT(instance, &debug_util_messenger_create_info, nullptr, &debug_messenger);
			DEBUG_ASSERT(create_debug_result == VK_SUCCESS);
#endif
		}

		// Create surface
		{
			VkWin32SurfaceCreateInfoKHR	sureface_create_info{};
			sureface_create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			sureface_create_info.hwnd = i_window->GetNaitiveWindowsHandler();
			sureface_create_info.hinstance = GetModuleHandle(nullptr);

			VkResult result = vkCreateWin32SurfaceKHR(instance, &sureface_create_info, nullptr, &surface);
			DEBUG_ASSERT(result == VK_SUCCESS);
		}

		// Get physical device info
		{
			uint32_t device_count = 0;
			vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

			DEBUG_ASSERT(device_count != 0);

			Array<VkPhysicalDevice> devices{};
			devices.Resize(device_count);
			vkEnumeratePhysicalDevices(instance, &device_count, devices.Data());
			for (const auto& device : devices)
			{
				physical_device = device;
				break;
			}

			DEBUG_ASSERT(physical_device != VK_NULL_HANDLE);

			vkGetPhysicalDeviceProperties(physical_device, &device_properties);
			vkGetPhysicalDeviceFeatures(physical_device, &device_features);

			bool device_qualified = false;
			device_qualified = (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && device_features.geometryShader);

			min_uniform_buffer_offset_alignment = device_properties.limits.minUniformBufferOffsetAlignment;
			max_sampler_anisotropy = device_properties.limits.maxSamplerAnisotropy;

			DEBUG_ASSERT(device_qualified);
		}

		// Get queue family info
		{
			uint32_t queue_family_count = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);

			Array<VkQueueFamilyProperties> queue_families;
			queue_families.Resize(queue_family_count);
			vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.Data());

			int i = 0;
			for (const auto& queue_family : queue_families)
			{

				if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					queue_family_indices.graphics_family = i;
				}

				VkBool32 present_support = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &present_support);
				if (present_support)
				{
					queue_family_indices.present_family = i;
				}

				i++;
			}
		}

		// Extensions related
		{
			// Check what type of extension does this graphics card has
			{
				uint32_t extension_count;
				vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, nullptr);
				availableExtensions.Resize(extension_count);
				vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, availableExtensions.Data());
			}

			// Check if this graphics card is able to make a swapchain
			bool requirement = false;
			device_extensions.PushBack(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
			//device_extensions.PushBack(VK_EXT_DEPTH_RANGE_UNRESTRICTED_EXTENSION_NAME);
			for (auto itr = availableExtensions.Begin(); itr != availableExtensions.End(); ++itr)
			{
				if (std::strcmp((*itr).extensionName, device_extensions.At(0)) == 0)
				{
					requirement = true;
					break;
				}
			}
			DEBUG_ASSERT(requirement);
		}

		// Create logical device
		{
			Array<VkDeviceQueueCreateInfo>  queue_create_infos;
			std::set<uint32_t> unique_queue_families = { queue_family_indices.graphics_family.value(), queue_family_indices.present_family.value() };

			float queue_priority = 1.0f;
			for (uint32_t queue_family : unique_queue_families)
			{
				VkDeviceQueueCreateInfo queue_create_info{};
				queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queue_create_info.queueFamilyIndex = queue_family;
				queue_create_info.queueCount = 1;
				queue_create_info.pQueuePriorities = &queue_priority;
				queue_create_infos.PushBack(queue_create_info);
			}

			device_features.samplerAnisotropy = VK_TRUE;

			VkDeviceCreateInfo device_create_info{};
			device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			device_create_info.pQueueCreateInfos = queue_create_infos.Data();
			device_create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.Size());
			device_create_info.pEnabledFeatures = &device_features;
			device_create_info.enabledExtensionCount = static_cast<uint32_t>(device_extensions.Size());
			device_create_info.ppEnabledExtensionNames = device_extensions.Data();

			VkResult create_device_result = vkCreateDevice(physical_device, &device_create_info, nullptr, &logical_device);
			DEBUG_ASSERT(create_device_result == VK_SUCCESS);
		}
	}

	void Device::CleanUp()
	{
		vkDestroyDevice(logical_device, nullptr);

#ifdef ENABLE_VULKAN_VALIDATION_LAYERS
		DestroyDebugUtilsMessengerEXT(instance, debug_messenger, nullptr);
#endif
		vkDestroySurfaceKHR(instance, surface, nullptr);

		vkDestroyInstance(instance, nullptr);
	}
}
#endif