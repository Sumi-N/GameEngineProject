#pragma once

#include "Define.h"
#include "SceneProxy.h"

class CubeMapProxy : public SceneProxy
{
public:
private:

	void InitTexture() override;
};

#ifdef ENGINE_GRAPHIC_OPENGL

inline void CubeMapProxy::InitTexture()
{
	textureids.resize(1);
	textureunits.resize(1);

	textureunits[0] = SKYBOX_BINDING_UNIT;

	glGenTextures(1, &textureids[0]);
	glActiveTexture(GL_TEXTURE0 + textureunits[0]);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureids[0]);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, mesh->textures[0]->width, mesh->textures[0]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, mesh->textures[0]->pixels.data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, mesh->textures[1]->width, mesh->textures[1]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, mesh->textures[1]->pixels.data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, mesh->textures[2]->width, mesh->textures[2]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, mesh->textures[2]->pixels.data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, mesh->textures[3]->width, mesh->textures[3]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, mesh->textures[3]->pixels.data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, mesh->textures[4]->width, mesh->textures[4]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, mesh->textures[4]->pixels.data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, mesh->textures[5]->width, mesh->textures[5]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, mesh->textures[5]->pixels.data());

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

#endif // ENGINE_GRAPHIC_OPENGL