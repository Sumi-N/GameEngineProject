#pragma once
#include "Define.h"
#include "Device.h"
#include "CommandBuffer.h"

namespace Tempest
{
	class Texture
	{
	public:
		void Init(const Device&, const CommandBuffer&, const TextureInfo&);
		void CleanUp();

		int width;
		int height;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		const VkImage& GetImage() const { return texture_image; }
		const VkImageView& GetImageView() const { return texture_image_view; }
		const VkSampler& GetImageSampler() const { return texture_sampler; }
	private:
		const Device* device;
		VkDeviceSize image_size;
		VkImage texture_image;
		VkImageView texture_image_view;
		VkSampler texture_sampler;
		VkDeviceMemory texture_image_memory;
#endif // ENGINE_GRAPHIC_VULKAN
	};
}