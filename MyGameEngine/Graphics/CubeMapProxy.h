#pragma once

#include "Define.h"
#include "SceneProxy.h"

enum class CubeMapType : uint8_t
{
	CubeMap = 0,
	EquirectangularMap = 1,
};

class CubeMapProxy : public SceneProxy
{
public:
	CubeMapProxy(){};
	CubeMapProxy(CubeMapType i_type){type = i_type;}
	CubeMapType type = CubeMapType::CubeMap;

#ifdef ENGINE_GRAPHIC_OPENGL
	GLuint GetCubeMapTextureID();
	GLuint GetCubeMapTextureUnit();
#endif // ENGINE_GRAPHIC_OPENGL

private:
	void InitTexture() override;
};

#ifdef ENGINE_GRAPHIC_OPENGL

inline void CubeMapProxy::InitTexture()
{
	if (type == CubeMapType::CubeMap)
	{
		for (int i = 0; i < 6; i++)
		{
			if (mesh->textures[i]->type != TextureType::SkyBox)
			{
				DEBUG_ASSERT(false);
			}
		}

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
	else if (type == CubeMapType::EquirectangularMap)
	{
		if (mesh->textures[0]->type != TextureType::SkyBox)
		{
			DEBUG_ASSERT(false);
		}

		//OwningPointer<HDRTextureAttribute> texture = mesh->textures[0];
		TextureAttribute * textureattribute = &*(mesh->textures[0]);
		HDRTextureAttribute* hdrtexture = dynamic_cast<HDRTextureAttribute *>(textureattribute);

		if (!hdrtexture)
		{
			DEBUG_ASSERT(false);
		}

		textureids.resize(1);
		textureunits.resize(1);

		textureunits[0] = HDR_BINDING_UNIT;

		glGenTextures(1, &textureids[0]);
		glActiveTexture(GL_TEXTURE0 + textureunits[0]);
		glBindTexture(GL_TEXTURE_2D, textureids[0]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, hdrtexture->width, hdrtexture->height, 0, GL_RGB, GL_FLOAT, hdrtexture->data2);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}

inline GLuint CubeMapProxy::GetCubeMapTextureID()
{
	return textureids[0];
}

inline GLuint CubeMapProxy::GetCubeMapTextureUnit()
{
	return textureunits[0];
}

#endif // ENGINE_GRAPHIC_OPENGL