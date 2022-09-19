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
};