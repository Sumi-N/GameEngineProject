#pragma once
#include "SceneProxy.h"

#ifdef ENGINE_GRAPHIC_OPENGL

void SceneProxy::Draw()
{
	state->BindShaderState();
	CheckDrawType(state->shader);

	for(int i = 0; i < meshes.Size(); i++)
	{ 				
		vbuffers[i].Bind();
		glDrawElements(static_cast<unsigned int>(drawtype), indexsizes[i], GL_UNSIGNED_INT, (void*)0);
		
	}

	state->UnBindShaderState();
}

// This function calls draw function without binding any shader.
// Calling this function is recommended if shader is already binded.
void SceneProxy::DrawMeshOnly()
{
	for (int i = 0; i < meshes.Size(); i++)
	{
		vbuffers[i].Bind();
		glDrawElements(static_cast<unsigned int>(drawtype), indexsizes[i], GL_UNSIGNED_INT, (void*)0);
	}
}


#endif // ENGINE_GRAPHIC_OPENGL