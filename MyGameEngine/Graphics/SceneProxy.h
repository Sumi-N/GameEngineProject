#pragma once

#include "Define.h"

class SceneProxy
{
public:

	void Init();
	void Draw();
	void CleanUp();

	OwningPointer<MeshComponent> mesh;

private:

	void InitBuffer();
	void InitMeshData();
	void InitTexture();
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