#pragma once
#include "Define.h"
#include "Device.h"
#include "CommandBuffer.h"

namespace Tempest
{
	class Texture
	{
	public:
		void Init(const Device&, const CommandBuffer&, TextureInfo);
		void CleanUp();

#ifdef ENGINE_GRAPHIC_VULKAN

		VkDeviceSize image_size;
		VkImageView texture_image_view;
		VkSampler texture_sampler;
	private:
		const Device* device;

		VkImage texture_image;
		VkDeviceMemory texture_image_memory;
#endif // ENGINE_GRAPHIC_VULKAN
	};
}