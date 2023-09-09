#include <set>

#include "CommandBuffer.h"
#include "Device.h"
#include "SwapChain.h"
#include "Sync.h"

#ifdef ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	namespace
	{
		bool CheckLayerSupport(const char* layer_name)
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

			const char* layer_names[] = {
#ifdef ENABLE_VULKAN_VALIDATION_LAYERS
				"VK_LAYER_KHRONOS_validation",
#endif
#ifdef ENABLE_RENDERDOC_CAPTURE
				"VK_LAYER_RENDERDOC_Capture",
#endif
				"DUMMY_LAYER",
			};
			instance_create_info.enabledLayerCount = ( sizeof(layer_names) / sizeof(layer_names[0]) ) - 1;
			instance_create_info.ppEnabledLayerNames =
				instance_create_info.enabledExtensionCount != 0 ? layer_names : nullptr;

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

		VkPhysicalDeviceProperties device_properties;
		VkPhysicalDeviceFeatures device_features;
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

			min_buffer_offset_alignment = static_cast<int>(device_properties.limits.minUniformBufferOffsetAlignment);
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

			bool has_adequate_queue = false;
			for (int i = 0; i < queue_families.Size(); i++)
			{

				if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					VkBool32 present_support = false;
					vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &present_support);
					if (present_support)
					{
						queue_family_index = i;
						has_adequate_queue = true;
					}
				}
			}
			DEBUG_ASSERT(has_adequate_queue);
		}

		Array<const char*> device_extensions;
		Array<VkExtensionProperties> availableExtensions{};
		// Extensions related
		{
			// Check what type of extension does this graphics card has
			{
				uint32_t extension_count;
				vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, nullptr);
				availableExtensions.Resize(extension_count);
				vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, availableExtensions.Data());
			}

			device_extensions.PushBack(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
			//device_extensions.PushBack(VK_EXT_DESCRIPTOR_BUFFER_EXTENSION_NAME);

			// Check if this graphics card is supporting exntensions
			for (int i = 0; i < device_extensions.Size(); i++)
			{
				bool available = false;
				for (auto itr = availableExtensions.Begin(); itr != availableExtensions.End(); ++itr)
				{
					if (std::strcmp((*itr).extensionName, device_extensions.At(i)) == 0)
					{
						available = true;
						break;
					}
				}
				DEBUG_ASSERT(available);
			}
		}

		// Create logical device
		{
			Array<VkDeviceQueueCreateInfo>  queue_create_infos;
			std::set<uint32_t> unique_queue_families = { queue_family_index };

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

			// Get queue
			vkGetDeviceQueue(logical_device, queue_family_index, 0, &queue);
		}

		// Create command pool and system command buffer
		{
			VkCommandPoolCreateInfo pool_create_info{};
			pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			pool_create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
			pool_create_info.queueFamilyIndex = queue_family_index;

			VkResult create_commandpool_result = vkCreateCommandPool(logical_device, &pool_create_info, nullptr, &commandpool);
			DEBUG_ASSERT(create_commandpool_result == VK_SUCCESS);

			VkCommandBufferAllocateInfo commandbuffer_allocate_info{};
			commandbuffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			commandbuffer_allocate_info.commandPool = commandpool;
			commandbuffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			commandbuffer_allocate_info.commandBufferCount = 1;

			VkResult create_commandbuffer_result = vkAllocateCommandBuffers(logical_device, &commandbuffer_allocate_info, &system_commandbuffer);
			DEBUG_ASSERT(create_commandbuffer_result == VK_SUCCESS);
		}
	}

	void Device::CleanUp()
	{
		vkDestroyCommandPool(logical_device, commandpool, nullptr);

		vkDestroyDevice(logical_device, nullptr);

#ifdef ENABLE_VULKAN_VALIDATION_LAYERS
		DestroyDebugUtilsMessengerEXT(instance, debug_messenger, nullptr);
#endif
		vkDestroySurfaceKHR(instance, surface, nullptr);

		vkDestroyInstance(instance, nullptr);
	}

	void Device::SubmitToQueue(const CommandBuffer& commandbuffer, const Fence* p_fence, const Semaphore* p_wait_semaphore, const Semaphore* p_signal_semaphore)
	{
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandbuffer.commandbuffer;

		VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		VkSemaphore wait_semaphore[] = { p_wait_semaphore->semaphore };
		if (p_wait_semaphore)
		{
			submitInfo.waitSemaphoreCount = 1;
			submitInfo.pWaitSemaphores = wait_semaphore;
			submitInfo.pWaitDstStageMask = wait_stages;
		}

		VkSemaphore signal_semaphore[] = { p_signal_semaphore->semaphore };
		if (p_signal_semaphore)
		{
			submitInfo.signalSemaphoreCount = 1;
			submitInfo.pSignalSemaphores = signal_semaphore;
		}

		auto queue_submi_result = vkQueueSubmit(queue, 1, &submitInfo, p_fence->fence);
		DEBUG_ASSERT(queue_submi_result == VK_SUCCESS);
	}

	void Device::Present(SwapChain& swapchain, uint32_t image_index, Semaphore& wait_semaphore)
	{
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &wait_semaphore.semaphore;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &swapchain.swapchain;
		presentInfo.pImageIndices = &image_index;

		vkQueuePresentKHR(queue, &presentInfo);
	}
}
#endif