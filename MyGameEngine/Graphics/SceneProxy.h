#pragma once

#include "Define.h"
#include "RenderState.h"

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
	DrawType drawtype;

	void InitBuffer();
	void InitMeshData();
	void CheckDrawType(Shader i_shader);
	void SetDrawType(DrawType i_drawtype){drawtype = i_drawtype;};
	void CleanUpBuffer();

#ifdef ENGINE_GRAPHIC_OPENGL

	// Buffer data
	GLuint vertexarrayid   = 0;
	GLuint vertexbufferid  = 0;
	GLuint indexbufferid   = 0;
	unsigned int indexsize = 0;

	// Texture data
	std::vector<GLuint> textureids;
	std::vector<GLuint> textureunits;

#endif // ENGINE_GRAPHIC_OPENGL
};