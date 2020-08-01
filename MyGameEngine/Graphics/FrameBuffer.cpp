#pragma once
#include "FrameBuffer.h"

void FrameBuffer::RenderToQuad()
{
#ifdef ENGINE_GRAPHIC_OPENGL
	RenderToQuad_OpenGL();
#endif // ENGINE_GRAPHIC_OPENGL
}

void FrameBuffer::RenderToCube()
{
#ifdef ENGINE_GRAPHIC_OPENGL
	RenderToCube_OpenGL();
#endif // ENGINE_GRAPHIC_OPENGL
}