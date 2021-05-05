#pragma once

#include "Define.h"
#include "Buffer.h"
#include "RenderState.h"

using namespace Tempest;

enum class DrawType : unsigned int
{
#ifdef ENGINE_GRAPHIC_OPENGL
	LINE     = GL_LINE,
	TRIANGLE = GL_TRIANGLES,
	PATCHES  = GL_PATCHES,
#endif // ENGINE_GRAPHIC_OPENGL
};

class SceneProxy
{

public:

	void Init();
	void AddRenderState(OwningPointer<RenderState>);
	void ReplaceRenderState(OwningPointer<RenderState>, int);
	void Draw();
	void DrawMeshOnly();
	void CleanUp();	

	OwningPointer<MeshComponent> mesh;
	std::vector<OwningPointer<RenderState>> states;

protected:

	DrawType originaltype = DrawType::TRIANGLE;
	DrawType drawtype     = DrawType::TRIANGLE;

	void InitBuffer();
	void CheckDrawType(Shader i_shader);
	void SetDrawType(DrawType i_drawtype){drawtype = i_drawtype;};
	void CleanUpBuffer();

	VertexBuffer vbuffer;
	IndexBuffer  ibuffer;

#ifdef ENGINE_GRAPHIC_OPENGL

	//// Buffer data
	unsigned int indexsize = 0;

#endif // ENGINE_GRAPHIC_OPENGL
};