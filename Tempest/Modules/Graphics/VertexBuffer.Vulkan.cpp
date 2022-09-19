#include "VertexBuffer.h"

namespace Tempest
{
#ifdef ENGINE_GRAPHIC_VULKAN

	void VertexBuffer::Bind() const
	{
	}

	void VertexBuffer::Unbind() const
	{
	}

	bool VertexBuffer::CheckStructDataSize(uint32_t i_size) const
	{
		return true;
	}

	void VertexBuffer::InitData(VertexBufferType i_type, uint32_t i_size, const void* i_data)
	{
	}

	void VertexBuffer::CleanUp() const
	{
	}

	IndexBuffer::IndexBuffer()
	{
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	void IndexBuffer::InitData(uint32_t i_size, const void* i_data)
	{
	}

	void IndexBuffer::CleanUp() const
	{

	}

#endif // ENGINE_GRAPHIC_OPENGL

}
