#pragma once
#include "Define.h"
#include "Device.h"
#include "VertexBuffer.h"
#include "UniformBuffer.h"
#include "Texture.h"

namespace Tempest
{
	class Descriptor
	{
	public:
		Descriptor() = default;
		~Descriptor() = default;

		void Init(const Device& i_device, const Shader& i_shader);
		void CleanUp();

		void Bind(const VertexBuffer& i_vertex);
		void Bind(const UniformBuffer& i_uniform, uint32_t i_binding);
		void Bind(const Texture& i_texture, uint32_t i_binding);

		uint32_t vertex_stride;

	private:
		const Device* device;

#ifdef ENGINE_GRAPHIC_VULKAN
	public:
		VkDescriptorSetLayout descriptorset_layout;
		VkDescriptorPool descriptor_pool;
		VkDescriptorSet descriptor_sets[Graphics::BufferingCount];

		Array<VkVertexInputAttributeDescription> attribute_descriptions;

	private:

#endif // ENGINE_GRAPHIC_VULKAN
	};
}