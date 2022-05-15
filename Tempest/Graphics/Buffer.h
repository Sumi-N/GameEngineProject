#pragma once

namespace Tempest
{
	namespace BufferData
	{
		enum class Type
		{
			None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
		};

		static uint32_t GetDataSize(Type type)
		{
			switch (type)
			{
			case Type::Float:    return 4;
			case Type::Float2:   return 4 * 2;
			case Type::Float3:   return 4 * 3;
			case Type::Float4:   return 4 * 4;
			case Type::Mat3:     return 4 * 3 * 3;
			case Type::Mat4:     return 4 * 4 * 4;
			case Type::Int:      return 4;
			case Type::Int2:     return 4 * 2;
			case Type::Int3:     return 4 * 3;
			case Type::Int4:     return 4 * 4;
			case Type::Bool:     return 1;
			}

			DEBUG_ASSERT(false);
			return 0;
		}

		struct Element
		{
			String name;
			Type type;
			uint32_t size;
			size_t offset;
			bool normalized;

			Element() = default;
			Element(Type i_type, const String& i_name, bool i_normalized = false)
				: type(i_type), name(i_name), size(GetDataSize(type)), offset(0), normalized(i_normalized) {}

			Element& operator= (const Element& i_element)
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

		class Layout
		{
		public:
			Layout() { }
			Layout(std::initializer_list<Element> i_elements)
			{
				elements.Convert(i_elements);
				CalculateOffsetsAndStride();
			}

			Array<Element> elements;
			uint32_t stride = 0;

			Layout& operator= (Layout i_layout)
			{
				elements = i_layout.elements;
				stride   = i_layout.stride;

				return *this;
			}

		private:

			void CalculateOffsetsAndStride()
			{
				size_t offset = 0;
				stride = 0;

				for (auto element = elements.Begin(); element != elements.End(); ++element)
				{
					element->offset = offset;
					offset += element->size;
					stride += element->size;
				}

			}
		};

	}

	enum class VertexBufferType : uint8_t
	{
		Mesh         = 0,
		SkeletonMesh = 1,
	};

	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		~VertexBuffer() = default;

		void Bind() const;
		void Unbind() const;

		bool CheckStructDataSize(uint32_t) const;
		void InitData(VertexBufferType, uint32_t, const void*);
		void CleanUp() const;

		const BufferData::Layout& GetLayout() const {return layout; }
		const void SetLayout(BufferData::Layout& i_layout) {layout = i_layout; }

	private:
		BufferData::Layout layout;

#ifdef ENGINE_GRAPHIC_OPENGL
		GLuint arrayid  = 0;
		GLuint bufferid = 0;
#endif // ENGINE_GRAPHIC_OPENGL
	};

	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		void InitData(uint32_t, const void*);
		void CleanUp() const;

	private:
#ifdef ENGINE_GRAPHIC_OPENGL
		GLuint bufferid = 0;
#endif // ENGINE_GRAPHIC_OPENGL
	};
}