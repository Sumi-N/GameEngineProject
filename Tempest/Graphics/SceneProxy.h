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
	SceneProxy()  = default;
	~SceneProxy() = default;

	void Init(const int);
	void AddRenderState(OwningPointer<RenderState>);
	void ReplaceRenderState(OwningPointer<RenderState>, int);
	void Draw();
	void DrawMeshOnly();
	void CleanUp();	

	ObservingPointer<Resource::Mesh>  mesh;
	ObservingPointer<Resource::SkeletonMesh> skeleton_mesh;
	Array<OwningPointer<RenderState>> states;
	
protected:

	const DrawType defaulttype = DrawType::TRIANGLE;
	DrawType drawtype          = DrawType::TRIANGLE;

	void InitBuffer(const int);
	void CheckDrawType(const Shader i_shader);
	void SetDrawType(DrawType i_drawtype){drawtype = i_drawtype;};
	void CleanUpBuffer() const;

	VertexBuffer vbuffer;
	IndexBuffer  ibuffer;

#ifdef ENGINE_GRAPHIC_OPENGL

	//// Buffer data
	unsigned int indexsize = 0;

#endif // ENGINE_GRAPHIC_OPENGL
};