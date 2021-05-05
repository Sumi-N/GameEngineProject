#pragma once
#include "SceneProxy.h"

#ifdef ENGINE_GRAPHIC_OPENGL

void SceneProxy::Draw()
{
	for(int i = 0; i < states.size(); i++)
	{ 
		states[i]->BindShaderState();

		CheckDrawType(states[i]->shader);		
		vbuffer.Bind();
		glDrawElements(static_cast<unsigned int>(drawtype), indexsize, GL_UNSIGNED_INT, (void*)0);

		states[i]->UnBindShaderState();
	}
}

// This function calls draw function without binding any shader.
// If shader is already binded, it will better call this.
void SceneProxy::DrawMeshOnly()
{
	vbuffer.Bind();
	glDrawElements(static_cast<unsigned int>(drawtype), indexsize, GL_UNSIGNED_INT, (void*)0);
}


#endif // ENGINE_GRAPHIC_OPENGL