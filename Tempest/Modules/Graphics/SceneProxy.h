#pragma once

#include "Define.h"
#include "VertexBuffer.h"
#include "RenderState.h"

using namespace Tempest;

enum class DrawType : unsigned int
{
#ifdef ENGINE_GRAPHIC_OPENGL
	LINE     = GL_LINE,
	TRIANGLE = GL_TRIANGLES,
	PATCHES  = GL_PATCHES,
#else
	LINE     = 0,
	TRIANGLE = 0,
	PATCHES  = 0,
#endif
};

class SceneProxy
{

public:
	SceneProxy() = default;
	~SceneProxy() = default;

	void Init(const int, const int);
	void ReplaceRenderState(Owner<RenderState>);
	void BindShader();
	void Draw(int);
	void UnbindShader();
	void DrawMeshOnly();
	void CleanUp();

	Owner<RenderState> state;
	Array<Observer<Mesh>> meshes;
	Array<int> mesh_indexs;

protected:

	constexpr static DrawType defaulttype = DrawType::TRIANGLE;
	DrawType drawtype{ defaulttype };

	void InitBuffer(const int);
	void CheckDrawType(const Shader i_shader);
	void SetDrawType(DrawType i_drawtype) { drawtype = i_drawtype; };
	void CleanUpBuffer() const;

	Array<VertexBuffer> vbuffers;
	//Array<IndexBuffer>  ibuffers;

	// Buffer data
	Array<unsigned int> indexsizes;
};