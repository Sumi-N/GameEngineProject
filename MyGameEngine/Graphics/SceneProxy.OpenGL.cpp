#include "SceneProxy.h"

#ifdef ENGINE_GRAPHIC_OPENGL

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

void SceneProxy::Draw()
{
	glBindVertexArray(vertexarrayid);
	glDrawElements(GL_TRIANGLES, indexsize, GL_UNSIGNED_INT, (void*)0);
}

void SceneProxy::BindMeshData(MeshComponent i_mesh)
{
	// Set vertex data to vertex buffer
	glBufferData(GL_ARRAY_BUFFER, i_mesh.data.size() * sizeof(i_mesh.data[0]), i_mesh.data.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_mesh.index.size() * sizeof(i_mesh.index[0]), i_mesh.index.data(), GL_STATIC_DRAW);

	// Enable vertex attribute
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(i_mesh.data[0]), (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(i_mesh.data[0]), (void*)(sizeof(Vec3f)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(i_mesh.data[0]), (void*)(2 * sizeof(Vec3f)));

	// Memorize index size for Draw() fucntion
	indexsize = i_mesh.index.size() * sizeof(i_mesh.index[0]);
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