#pragma once

#include "Define.h"

class SkyBox : public Object
{
public:
	void Boot() override;
};

inline void SkyBox::Boot()
{
	CubeMapMeshComponent* mesh = new CubeMapMeshComponent();
	Entity::RegisterMeshComponent(mesh);
	mesh->owner = Entity::Query(this).p;

	TextureAttribute* texture[6];
	const char* filename[6] =
	{
		PATH_SUFFIX TEXTURE_PATH SKYBOX_POSX,
		PATH_SUFFIX TEXTURE_PATH SKYBOX_NEGX,
		PATH_SUFFIX TEXTURE_PATH SKYBOX_POSY,
		PATH_SUFFIX TEXTURE_PATH SKYBOX_NEGY,
		PATH_SUFFIX TEXTURE_PATH SKYBOX_POSZ,
		PATH_SUFFIX TEXTURE_PATH SKYBOX_NEGZ,
	};

#pragma omp parallel for
	for (int i = 0; i < 6; i++)
	{
		texture[i] = new TextureAttribute();
		texture[i]->Load(filename[i], TextureType::None);
		OwningPointer<TextureAttribute> handler(texture[i]);
		mesh->textures.push_back(handler);
	}

	Shader* skyboxshader = new Shader(PATH_SUFFIX SHADER_PATH SKYBOX_VERT, PATH_SUFFIX SHADER_PATH SKYBOX_FRAG);

	CubeMapProxy* skyboxproxy = new CubeMapProxy();
	skyboxproxy->mesh = mesh;

	SceneEntity::RegisterSkyBox(skyboxproxy, skyboxshader);
}
