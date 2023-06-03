#pragma once
#include "Define.h"

#include "Graphics/Device.h"
#include "Graphics/VertexBuffer.h"

namespace Tempest
{
	class PrimitiveDrawer
	{
	public:
		static void Init(const Device* pDevice);

		static void DrawCube(const CommandBuffer& i_commandbuffer);
		static void DrawQuad(const CommandBuffer& i_commandbuffer);

		static VertexBuffer VertexBufferCube;
		static VertexBuffer VertexBufferQuad;

	private:
		static void InitCube(const Device* pDevice);
		static void InitQuad(const Device* pDevice);
		static void InitLine(const Device* pDevice);

		//static void InitBasicShader();
		//static void DrawLineWithShader(Vec3f, Vec3f);
		//static Shader shader_basic_green_line;
	};
}
