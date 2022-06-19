#include "Device.h"

namespace Tempest
{
#ifdef ENGINE_GRAPHIC_VULKAN
	namespace
	{
		bool CheckValidationLayerSupport(const char* layer_name)
		{
			uint32_t layer_count;
			vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

			Tempest::Array<VkLayerProperties> available_layers;
			available_layers.Resize(layer_count);
			vkEnumerateInstanceLayerProperties(&layer_count, available_layers.Data());


			for (const auto& layerProperties : available_layers)
			{
				if (strcmp(layer_name, layerProperties.layerName) == 0)
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

	void Device::Initialize(Array<const char*> i_extensions)
	{
		// Initialize instance
		VkApplicationInfo app_info{};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pApplicationName = "Tempest";
		app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.pEngineName = nullptr;
		app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.apiVersion = VK_API_VERSION_1_2;

		VkInstanceCreateInfo instance_create_info{};
		instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instance_create_info.pApplicationInfo = &app_info;
		instance_create_info.enabledExtensionCount = static_cast<uint32_t>(i_extensions.Size());
		instance_create_info.ppEnabledExtensionNames = i_extensions.Data();

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
		if (vkCreateInstance(&instance_create_info, nullptr, &instance) != VK_SUCCESS)
		{
			DEBUG_ASSERT(false);
		}
	}
#endif
}