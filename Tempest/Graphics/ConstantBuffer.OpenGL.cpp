#pragma once
#include "ConstantBuffer.h"

#ifdef  ENGINE_GRAPHIC_OPENGL
ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
}

void ConstantBuffer::Init(ConstantData::Index i_index)
{
	index = static_cast<GLuint>(i_index);
	size = static_cast<GLsizeiptr>(ConstantData::GetDataSize(i_index));

	glGenBuffers(1, &bufferid);
	glBindBuffer(GL_UNIFORM_BUFFER, bufferid);
	glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, index, bufferid);
}

void ConstantBuffer::Update(const void* const i_data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, bufferid);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, size, i_data);
}
#endif // ENGINE_GRAPHIC_OPENGL