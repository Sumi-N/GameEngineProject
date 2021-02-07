#pragma once
#include "Define.h"
#include "Shader.h"

class DrawPrimitive
{
public:
	static void Init();

	static void DebugInit();
	static void DebugDraw();

	static void InitBasicShader();
	static void InitCube();
	static void InitQuad();
	static void InitLine();

	static void DrawCube();
	static void DrawQuad();

	static void DrawLineWithShader(Vec3f, Vec3f);

private:

	static Shader shader_basic_green_line;

#ifdef ENGINE_GRAPHIC_OPENGL

	static unsigned int vao_cube;
	static unsigned int vao_quad;
	static unsigned int vao_line;

	static unsigned int vbo_cube;
	static unsigned int vbo_quad;
	static unsigned int vbo_line;

#endif // ENGINE_GRAPHIC_OPENGL
};