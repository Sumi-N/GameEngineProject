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
		void Update(int i_index, void* i_uniform_data, size_t i_uniform_size);

		static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef ENGINE_GRAPHIC_VULKAN
		VkDescriptorSetLayout descriptorset_layout;
		VkDescriptorPool descriptor_pool;
		VkDescriptorSet descriptor_sets[MAX_FRAMES_IN_FLIGHT];

		VkBuffer uniformbuffers[MAX_FRAMES_IN_FLIGHT];
		VkDeviceMemory uniformbuffers_memory[MAX_FRAMES_IN_FLIGHT];
	private:
		const Device* device;
#endif // ENGINE_GRAPHIC_VULKAN
	};
}