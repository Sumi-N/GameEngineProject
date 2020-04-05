#include "SceneProxy.h"

#ifdef ENGINE_GRAPHIC_OPENGL

void SceneProxy::Draw()
{
	for (int i = 0; i < textureunits.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + textureunits[i]);
		glBindTexture(GL_TEXTURE_2D, textureids[i]);
	}

	glBindVertexArray(vertexarrayid);
	glDrawElements(static_cast<unsigned int>(drawtype), indexsize, GL_UNSIGNED_INT, (void*)0);

	// Unbind textures
	for (int i = 0; i < textureunits.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + textureunits[i]);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
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

void SceneProxy::InitTexture()
{
	textureids.resize(mesh->textures.size());
	textureunits.resize(mesh->textures.size());

	for (int i = 0; i < textureunits.size(); i++)
	{
		textureunits[i] = i + TEXTURE_UNIT_BINDING_OFFSET;
		glGenTextures(1, &textureids[i]);
		glActiveTexture(GL_TEXTURE0 + textureunits[i]);
		glBindTexture(GL_TEXTURE_2D, textureids[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mesh->textures[i]->width, mesh->textures[i]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, mesh->textures[i]->pixels.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
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
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(mesh->data[0]), (void*)(2 * sizeof(Vec3f) + sizeof(Vec2f)));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(mesh->data[0]), (void*)(3 * sizeof(Vec3f) + sizeof(Vec2f)));

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