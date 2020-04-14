#pragma once

#include "Define.h"

class EquirectangularSkyBox : public Object
{
public:
	void Boot() override;
};

inline void EquirectangularSkyBox::Boot()
{
	Object::Boot();

	CubeMapMeshComponent* mesh = new CubeMapMeshComponent();
	Entity::RegisterMeshComponent(mesh);
	mesh->owner = Entity::Query(this).p;

	HDRTextureAttribute* texture = new HDRTextureAttribute();
	texture->Load(PATH_SUFFIX TEXTURE_PATH SKYBOX_HDR_PINTREE, TextureType::SkyBox);
	OwningPointer<TextureAttribute> handler(texture);
	mesh->textures.push_back(handler);

	Shader* shader = new Shader(PATH_SUFFIX SHADER_PATH SKYBOX_VERT, PATH_SUFFIX SHADER_PATH SKYBOX_FRAG);

	CubeMapProxy* proxy = new CubeMapProxy();
	proxy->mesh = mesh;
	proxy->type = CubeMapType::EquirectangularMap;

	SceneEntity::RegisterSkyBox(proxy, shader);
}