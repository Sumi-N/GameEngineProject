#pragma once
#include "Shader.h"

#ifdef ENGINE_GRAPHIC_OPENGL

void Shader::BindShader()
{
	glUseProgram(programid);
}

#endif // ENGINE_GRAPHIC_OPENGL