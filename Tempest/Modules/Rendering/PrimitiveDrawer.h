#pragma once
#include "Define.h"

namespace Tempest
{
	class PrimitiveDrawer
	{
	public:
		static void Init();

		static void DrawCube(const CommandBuffer& i_commandbuffer);
		static void DrawQuad(const CommandBuffer& i_commandbuffer);

	private:
		static void InitCube();
		static void InitQuad();
		static void InitLine();

		//static void InitBasicShader();
		//static void DrawLineWithShader(Vec3f, Vec3f);
		//static Shader shader_basic_green_line;
	};
}
