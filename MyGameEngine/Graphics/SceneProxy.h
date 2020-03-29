#pragma once

#include "Define.h"

enum class DrawType : unsigned int
{
#ifdef ENGINE_GRAPHIC_OPENGL
	TRIANGLE = GL_TRIANGLES,
	PATCHES = GL_PATCHES,
#endif // ENGINE_GRAPHIC_OPENGL
};

class SceneProxy
{

public:

	void Init();
	void Draw();
	void CleanUp();
	void SetDrawType(DrawType i_drawtype){drawtype = i_drawtype;};

	OwningPointer<MeshComponent> mesh;

protected:

	DrawType drawtype = DrawType::TRIANGLE;

	void InitBuffer();
	void InitMeshData();
	virtual void InitTexture();
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