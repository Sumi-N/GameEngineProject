#pragma once
#include "Define.h"

class  SkyBox : public CubeMap
{
public:
	void Boot() override;
};

inline void SkyBox::Boot()
{
	CubeMap::Boot();

	mesh = ObjectFactory<MeshComponent>::Create();
	mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_CUBEMAP);


	OwningPointer<TextureAttribute> texture = ObjectFactory<TextureAttribute>::Create();
	texture->Load(PATH_SUFFIX TEXTURE_PATH SKYBOX_HDR_BLACK, TextureType::SkyBox);

	const char* shaderpaths[] =
	{
		PATH_SUFFIX SHADER_PATH SKYBOX_VERT,
		nullptr,
		nullptr,
		nullptr,
		PATH_SUFFIX SHADER_PATH SKYBOX_FRAG,
	};

	effect = ObjectFactory<EffectComponent>::Create();
	OwningPointer<Object> handler = Entity::Query(this).p;
	effect->owner = handler;
	effect->RegisterShaderPath(shaderpaths);
	effect->SetTexture(texture);
}