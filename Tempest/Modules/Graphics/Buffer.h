#pragma once
#include "Define.h"

namespace Tempest
{
	enum class BufferFormat
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t GetBufferLayoutTypeSize(BufferFormat i_type)
	{
		switch (i_type)
		{
		case BufferFormat::Float:    return 4;
		case BufferFormat::Float2:   return 4 * 2;
		case BufferFormat::Float3:   return 4 * 3;
		case BufferFormat::Float4:   return 4 * 4;
		case BufferFormat::Mat3:     return 4 * 3 * 3;
		case BufferFormat::Mat4:     return 4 * 4 * 4;
		case BufferFormat::Int:      return 4;
		case BufferFormat::Int2:     return 4 * 2;
		case BufferFormat::Int3:     return 4 * 3;
		case BufferFormat::Int4:     return 4 * 4;
		case BufferFormat::Bool:     return 1;
		}

		DEBUG_ASSERT(false);
		return 0;
	}

	struct BufferUnit
	{
		String name;
		BufferFormat type;
		uint32_t size;
		size_t offset;
		bool normalized;

		BufferUnit() = default;
		BufferUnit(BufferFormat i_type, const String& i_name, bool i_normalized = false)
			: type(i_type), name(i_name), size(GetBufferLayoutTypeSize(type)), offset(0), normalized(i_normalized) {}

		BufferUnit& operator= (const BufferUnit& i_element)
		{
			name = String();
			name = i_element.name;
			type = i_element.type;
			size = i_element.size;
			offset = i_element.offset;
			normalized = i_element.normalized;

			return *this;
		}
	};

	enum BufferType
	{
		Vetex, Index, Uniform
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const Device& i_device, BufferType i_type, std::initializer_list<BufferUnit> i_units)
		{
			units.Convert(i_units);
			CalculateOffsetsAndStride(i_device, i_type);
		}

		Array<BufferUnit> units;
		uint32_t stride = 0;

		BufferLayout& operator= (BufferLayout i_layout)
		{
			units  = i_layout.units;
			stride = i_layout.stride;

			return *this;
		}

	private:
		void CalculateOffsetsAndStride(const Device& i_device, BufferType i_type)
		{
			size_t offset = 0;
			stride = 0;

			for (auto unit = units.Begin(); unit != units.End(); ++unit)
			{
				if (i_type == Uniform)
				{
					// TODO : This is not strictly correct, need to fix later
					offset = (offset / i_device.min_buffer_offset_alignment + 1) * i_device.min_buffer_offset_alignment;
				}

				unit->offset = offset;
				offset += unit->size;
				stride += unit->size;
			}
		}
	};

	class Buffer
	{
	public:
		Buffer() =  default;
		virtual ~Buffer() = default;

		BufferLayout layout;

	private:

#ifdef ENGINE_GRAPHIC_VULKAN
	public:

	private:

	protected:
		static uint32_t FindMemoryType(VkPhysicalDevice physical_device, uint32_t type_filter, VkMemoryPropertyFlags properties)
		{

			VkPhysicalDeviceMemoryProperties memory_properties;
			vkGetPhysicalDeviceMemoryProperties(physical_device, &memory_properties);

			for (uint32_t i = 0; i < memory_properties.memoryTypeCount; i++)
			{
				if ((type_filter & (1 << i)) && (memory_properties.memoryTypes[i].propertyFlags & properties) == properties)
				{
					return i;
				}
			}

			DEBUG_ASSERT(false)
				return 0;
		}

		static 	void CreateBuffer(VkPhysicalDevice physical_device, VkDevice logical_device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory)
		{
			VkBufferCreateInfo buffer_info{};
			buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			buffer_info.size = size;
			buffer_info.usage = usage;
			buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			auto create_result = vkCreateBuffer(logical_device, &buffer_info, nullptr, &buffer);
			DEBUG_ASSERT(create_result == VK_SUCCESS)

				VkMemoryRequirements memory_requirements;
			vkGetBufferMemoryRequirements(logical_device, buffer, &memory_requirements);

			VkMemoryAllocateInfo alloc_info{};
			alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			alloc_info.allocationSize = memory_requirements.size;
			alloc_info.memoryTypeIndex = FindMemoryType(physical_device, memory_requirements.memoryTypeBits, properties);

			auto allocate_result = vkAllocateMemory(logical_device, &alloc_info, nullptr, &buffer_memory);
			DEBUG_ASSERT(allocate_result == VK_SUCCESS)

				vkBindBufferMemory(logical_device, buffer, buffer_memory, 0);
		}
#endif
	};
}