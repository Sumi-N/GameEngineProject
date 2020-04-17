#pragma once

#include "Define.h"
#include "RenderState.h"

class SceneProxy
{

public:

	void Init();
	void AddRenderState(OwningPointer<RenderState>);
	void Draw();
	void CleanUp();	

	OwningPointer<MeshComponent> mesh;
	std::vector<OwningPointer<RenderState>> states;

protected:

	DrawType drawtype = DrawType::TRIANGLE;

	void InitBuffer();
	void InitMeshData();
	virtual void InitTexture();
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