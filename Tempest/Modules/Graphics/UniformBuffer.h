#pragma once
#include "Define.h"
#include "Device.h"

namespace Tempest
{
	class UniformBuffer
	{
	public:
		void Init(const Device& i_device, const Shader& i_shader);
		void CleanUp();
		void Update(int i_index, void* i_data, size_t i_size, size_t i_offset) const;

		const VkDescriptorSetLayout& GetDescriptorLayout() const { return descriptorset_layout; }
		const VkDescriptorSet& GetDescriptorSet(int index) const { return descriptor_sets[index]; }

#ifdef ENGINE_GRAPHIC_VULKAN
	private:
		const Device* device;
		int buffer_count;
		size_t buffer_offset_alignment;

		VkDescriptorSetLayout descriptorset_layout;
		Array<VkBuffer> uniformbuffers;
		Array<VkDeviceMemory> uniformbuffers_memories;
		VkDescriptorPool descriptor_pool;
		Array<VkDescriptorSet> descriptor_sets;
#endif // ENGINE_GRAPHIC_VULKAN
	};
}