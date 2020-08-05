#pragma once
#include "SceneProxy.h"

#ifdef ENGINE_GRAPHIC_OPENGL

void SceneProxy::Draw()
{
	for(int i = 0; i < states.size(); i++)
	{ 
		states[i]->BindShaderState();

		CheckDrawType(states[i]->shader);
		glBindVertexArray(vertexarrayid);
		glDrawElements(static_cast<unsigned int>(drawtype), indexsize, GL_UNSIGNED_INT, (void*)0);

		states[i]->UnBindShaderState();
	}
}

// This function will only call draw element without bind any shader.
// If shader is already binded, it will better call this.
void SceneProxy::DrawMeshOnly()
{
	glBindVertexArray(vertexarrayid);
	glDrawElements(static_cast<unsigned int>(drawtype), indexsize, GL_UNSIGNED_INT, (void*)0);
}

void SceneProxy::InitBuffer()
{
	// Create vertex array 
	glGenVertexArrays(1, &vertexarrayid);
	glBindVertexArray(vertexarrayid);

	// Create vertex buffer 
	glGenBuffers(1, &vertexbufferid);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferid);

	// Create index buffer
	glGenBuffers(1, &indexbufferid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferid);
}

void SceneProxy::InitMeshData()
{
	// Set vertex data to vertex buffer
	glBufferData(GL_ARRAY_BUFFER, mesh->data.size() * sizeof(mesh->data[0]), mesh->data.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->index.size() * sizeof(mesh->index[0]), mesh->index.data(), GL_STATIC_DRAW);

	// Enable vertex attribute
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mesh->data[0]), (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(mesh->data[0]), (void*)(sizeof(Vec3f)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(mesh->data[0]), (void*)(2 * sizeof(Vec3f)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(mesh->data[0]), (void*)(2 * sizeof(Vec3f) + 2 * sizeof(Vec2f)));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(mesh->data[0]), (void*)(3 * sizeof(Vec3f) + 2 * sizeof(Vec2f)));

	// Memorize index size for Draw() fucntion
	indexsize = static_cast<unsigned int>(mesh->index.size()) * sizeof(mesh->index[0]);
}

void SceneProxy::CleanUpBuffer()
{
	// Unbind the vertex array
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &vertexarrayid);
	glDeleteBuffers(1, &vertexbufferid);
	glDeleteBuffers(1, &indexbufferid);
}

#endif // ENGINE_GRAPHIC_OPENGL