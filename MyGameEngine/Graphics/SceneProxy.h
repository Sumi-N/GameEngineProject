#pragma once

#include "Define.h"

class SceneProxy
{
public:
	void Init(MeshComponent i_mesh);
	void Draw();
	void CleanUp();

private:

	void InitBuffer();
	void CleanUpBuffer();
	void BindMeshData(MeshComponent i_mesh);

#ifdef ENGINE_GRAPHIC_OPENGL
	GLuint vertexarrayid   = 0;
	GLuint vertexbufferid  = 0;
	GLuint indexbufferid   = 0;
	unsigned int indexsize = 0;
#endif // ENGINE_GRAPHIC_OPENGL
};

inline void SceneProxy::Init(MeshComponent i_mesh)
{
	InitBuffer();
	BindMeshData(i_mesh);
}

inline void SceneProxy::CleanUp()
{

}