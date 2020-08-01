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
	texture->Load(PATH_SUFFIX TEXTURE_PATH SKYBOX_HDR_PINTREE, TextureType::SkyBox);

	const char* shaderpaths[] =
	{
		PATH_SUFFIX SHADER_PATH SKYBOX_VERT,
		nullptr,
		nullptr,
		nullptr,
		PATH_SUFFIX SHADER_PATH SKYBOX_FRAG,
	};

	effect = ObjectFactory<EffectComponent>::Create();
	effect->owner = Entity::Skybox;
	effect->RegisterShaderPath(shaderpaths);
	effect->SetTexture(texture);
}