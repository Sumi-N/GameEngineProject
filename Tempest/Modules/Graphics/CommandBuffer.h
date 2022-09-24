#pragma once
#include "Define.h"
#include "Device.h"

namespace Tempest
{
	class CommandBuffer
	{
	public:
		CommandBuffer() = default;
		~CommandBuffer() = default;

		void Init(const Device& i_device);
		void CleanUp();

	private:

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		const VkCommandBuffer& GetBuffer() const { return commandbuffer; };

	private:
		const Device* device;
		VkCommandBuffer commandbuffer;
#endif // ENGINE_GRAPHIC_VULKAN

	};
}