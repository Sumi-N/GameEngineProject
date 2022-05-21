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
	SceneProxy() = default;
	~SceneProxy() = default;

	void Init(const int, const int);
	void ReplaceRenderState(Owner<RenderState>);
	void BindShader();
	void Draw(int);
	void UnBindShader();	
	void DrawMeshOnly();
	void CleanUp();

	Owner<RenderState> state;
	Array<Observer<Resource::Mesh>> meshes;
	Array<int> mesh_indexs;

protected:

	constexpr static DrawType defaulttype = DrawType::TRIANGLE;
	DrawType drawtype{ defaulttype };

	void InitBuffer(const int);
	void CheckDrawType(const Shader i_shader);
	void SetDrawType(DrawType i_drawtype) { drawtype = i_drawtype; };
	void CleanUpBuffer() const;

	Array<VertexBuffer> vbuffers;
	Array<IndexBuffer>  ibuffers;

#ifdef ENGINE_GRAPHIC_OPENGL

	//// Buffer data
	Array<unsigned int> indexsizes;

#endif // ENGINE_GRAPHIC_OPENGL
};