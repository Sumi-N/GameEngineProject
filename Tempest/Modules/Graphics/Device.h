#pragma once
#include "Define.h"
#include "Window.h"

namespace Tempest
{
	class CommandBuffer;
	class Fence;
	class SwapChain;
	class Semaphore;

	class Device
	{
	public:
		Device() = default;
		~Device() = default;

		void Init(Window* i_window);
		void CleanUp();
		void SubmitToQueue(const CommandBuffer& commandbuffer,
					const Fence* p_fence,
					const Semaphore* p_wait_semaphore,
					const Semaphore* p_signal_semaphore);
		void Present(SwapChain& swapchain, uint32_t image_index, Semaphore& semaphore);

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