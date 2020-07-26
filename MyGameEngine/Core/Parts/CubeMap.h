#pragma once

#include "Define.h"
#include "Object.h"
#include "MeshComponent.h"
#include "EffectComponent.h"

class CubeMap : public Object
{
public:
	CubeMap(): mesh(nullptr), effect(nullptr){}
	void Boot() override;
	MeshComponent* mesh;
	EffectComponent* effect;
};

inline void CubeMap::Boot()
{
	Object::Boot();
	mesh = new MeshComponent();
	mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_CUBEMAP);
	

	TextureAttribute* texture = new TextureAttribute();
	texture->Load(PATH_SUFFIX TEXTURE_PATH SKYBOX_HDR_BLACK, TextureType::SkyBox);

	const char* shaderpaths[] =
	{
		PATH_SUFFIX SHADER_PATH SKYBOX_VERT,
		nullptr,
		nullptr,
		nullptr,
		PATH_SUFFIX SHADER_PATH SKYBOX_FRAG,
	};

	effect = new EffectComponent();
	OwningPointer<Object> handler;
	handler = static_cast<Object *>(this);
	effect->owner = handler;
	effect->RegisterShaderPath(shaderpaths);
	effect->SetTexture(texture);
}
