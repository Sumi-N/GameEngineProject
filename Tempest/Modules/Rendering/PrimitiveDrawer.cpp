#include "Define.h"
#include "PrimitiveDrawer.h"
#include "GraphicsFramework.h"

#ifdef  ENGINE_GRAPHIC_VULKAN
namespace Tempest
{
	VertexBuffer PrimitiveDrawer::VertexBufferCube;
	VertexBuffer PrimitiveDrawer::VertexBufferQuad;

	BufferLayout VertexLayoutCube({
		BufferUnit(BufferFormat::Float3, "vertex"),
		BufferUnit(BufferFormat::Float3, "normal"),
		BufferUnit(BufferFormat::Float2, "texcoord") });
	BufferLayout VertexLayoutQuad({
		BufferUnit(BufferFormat::Float3, "vertex"),
		BufferUnit(BufferFormat::Float2, "texcoord") });

	void PrimitiveDrawer::Init(const Device* pDevice)
	{
		InitCube(pDevice);
		InitQuad(pDevice);
		InitLine(pDevice);
	}


	//Shader DrawPrimitive::shader_basic_green_line;
	//
	//void DrawPrimitive::InitBasicShader()
	//{
	//	shader_basic_green_line.SetShader(PATH_SUFFIX SHADER_PATH DEBUG_LINE_VERT, PATH_SUFFIX SHADER_PATH DEBUG_LINE_FRAG);
	//	shader_basic_green_line.LoadShader();
	//}

	void PrimitiveDrawer::InitCube(const Device* pDevice)
	{
		static float vertices[] = {
			// back face
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
			// front face
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			// left face
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			// right face
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
			// bottom face
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			// top face
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
		};

		constexpr uint32_t indices[] = {
			 0,  1,  2,  3,  4,  5,
			 6,  7,  8,  9, 10, 11,
			12, 13, 14, 15, 16, 17,
			18, 19, 20, 21, 22, 23,
			24, 25, 26, 27, 28, 29,
			30, 31, 32, 33, 34, 35
		};

		uint32_t vetex_size = static_cast<uint32_t>(sizeof(vertices));
		uint32_t index_size = static_cast<uint32_t>(sizeof(indices));
		VertexBufferCube.Init(*pDevice, VertexLayoutCube, vertices, vetex_size, indices, index_size);
	}

	void PrimitiveDrawer::InitQuad(const Device* pDevice)
	{
		constexpr float vertices[] = {
			// positions
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};

		constexpr uint32_t indices[] = {
			0, 1, 2, // first triangle
			1, 2, 3  // second triangle
		};

		uint32_t vetex_size = static_cast<uint32_t>(sizeof(vertices));
		uint32_t index_size = static_cast<uint32_t>(sizeof(indices));
		VertexBufferQuad.Init(*pDevice, VertexLayoutQuad, vertices, vetex_size, indices, index_size);
	}

	void PrimitiveDrawer::InitLine(const Device* pDevice)
	{
		constexpr GLfloat linevertex[] =
		{
			0, 0, -1,
			0, 0, 1,
		};

		//glGenVertexArrays(1, &vao_line);
		//glGenBuffers(1, &vbo_line);
		//glBindVertexArray(vao_line);
		//glBindBuffer(GL_ARRAY_BUFFER, vbo_line);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(linevertex), &linevertex, GL_STATIC_DRAW);
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}

	void PrimitiveDrawer::DrawCube(const CommandBuffer& i_commandbuffer)
	{
		i_commandbuffer.Draw(VertexBufferCube);
	}

	void PrimitiveDrawer::DrawQuad(const CommandBuffer& i_commandbuffer)
	{
		i_commandbuffer.Draw(VertexBufferQuad);
	}

	//void PrimitiveDrawer::DrawLineWithShader(Vec3f start_point, Vec3f end_point)
	//{
	//	GLfloat linevertex[] =
	//	{
	//		start_point.x, start_point.y, start_point.z,
	//		end_point.x, end_point.y, end_point.z,
	//	};

	//	shader_basic_green_line.BindShader();
	//	glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(float), (void*)linevertex);
	//	glBindVertexArray(vao_line);
	//	glDrawArrays(GL_LINES, 0, 2);
	//	glBindVertexArray(0);
	//}
}
#endif //  ENGINE_GRAPHIC_VULKAN