#pragma once
#include "Define.h"
#include "Device.h"

namespace Tempest
{
	class Texture
	{
	public:
		Texture() = default;
		~Texture() = default;

		void Init(const Device&, const TextureInfo&);
		void CleanUp();

		int width;
		int height;

	private:
		const Device* device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkDeviceSize size;
		VkFormat format;
		VkImageAspectFlags aspect;

		VkImage image;
		VkImageView image_view;
		VkSampler sampler;

	private:
		VkDeviceMemory texture_image_memory;

#endif // ENGINE_GRAPHIC_VULKAN
	};
}