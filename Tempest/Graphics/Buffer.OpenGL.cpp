#include "Buffer.h"

namespace Tempest
{
#ifdef ENGINE_GRAPHIC_OPENGL

	VertexBuffer::VertexBuffer()
	{
		// Set Layout
		BufferData::Element vertex(BufferData::Type::Float3, "vertex");
		BufferData::Element normal(BufferData::Type::Float3, "normal");
		BufferData::Element uvcoord(BufferData::Type::Float2, "uvcoord");
		BufferData::Element tangent(BufferData::Type::Float3, "tangent");
		BufferData::Element bitangent(BufferData::Type::Float3, "bitangent");		

		BufferData::Layout vbufflayout({vertex, normal, uvcoord, tangent, bitangent});
		
		SetLayout(vbufflayout);
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	void VertexBuffer::Bind() const
	{
		glBindVertexArray(arrayid);
	}

	void VertexBuffer::Unbind() const
	{

	}

	bool VertexBuffer::CheckStructDataSize(uint32_t i_size) const
	{
		if (i_size == layout.stride)
		{
			return true;
		}
		DEBUG_ASSERT(false);
		return false;
	}

	void VertexBuffer::InitData(uint32_t i_size, const void* i_data)
	{
		// Create vertex array 
		glGenVertexArrays(1, &arrayid);
		glBindVertexArray(arrayid);

		// Create vertex buffer 
		glGenBuffers(1, &bufferid);
		glBindBuffer(GL_ARRAY_BUFFER, bufferid);

		// Fill in the data to the vertex buffer
		glBufferData(GL_ARRAY_BUFFER, i_size, i_data, GL_STATIC_DRAW);
		for (int i = 0; i < layout.elemetns.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, layout.elemetns[i].size / sizeof(float), GL_FLOAT, GL_FALSE, layout.stride, (void*)(layout.elemetns[i].offset));
		}

		
	}

	void VertexBuffer::CleanUp() const
	{
		// Unbind the vertex array
		glBindVertexArray(0);

		glDeleteVertexArrays(1, &arrayid);
		glDeleteBuffers(1, &bufferid);
	}

	IndexBuffer::IndexBuffer()
	{

	}

	IndexBuffer::~IndexBuffer()
	{

	}

	void IndexBuffer::InitData(uint32_t i_size, const void* i_data)
	{
		// Create index buffer
		glGenBuffers(1, &bufferid);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferid);

		// Set the data to index buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, i_data, GL_STATIC_DRAW);
	}

	void IndexBuffer::CleanUp() const
	{
		glDeleteBuffers(1, &bufferid);
	}

#endif // ENGINE_GRAPHIC_OPENGL

}
