#pragma once

#include <Core/Math/Vector.h>
#include <PremadeParts/PremadeObject.h>

#include <Graphics/SceneEntity.h>

class Teapot : public PremadeObjebct
{
	void Boot() override;
	void Init() override;
	void Update(float i_dt) override;
};

inline void Teapot::Boot()
{
	PremadeObjebct::Boot();

	mesh->Load(PATH_SUFFIX MESH_PATH "teapot.obj");

	OwningPointer<TextureAttribute> teapottexture  = OwningPointer<TextureAttribute>::Create(teapottexture);
	OwningPointer<TextureAttribute> teapottexture2 = OwningPointer<TextureAttribute>::Create(teapottexture2);
	OwningPointer<TextureAttribute> teapottexture3 = OwningPointer<TextureAttribute>::Create(teapottexture3);

	teapottexture->Load(PATH_SUFFIX TEXTURE_PATH "albedo/brickwall.png", TextureType::PB_Diffuse);
	teapottexture2->Load(PATH_SUFFIX TEXTURE_PATH "albedo/brickwall.png", TextureType::PB_Specular);
	teapottexture3->Load(PATH_SUFFIX TEXTURE_PATH "normal/brickwall_normal.png", TextureType::PB_Normal);

	const char* shaderpaths[] =
	{
		PATH_SUFFIX SHADER_PATH BLINN_PHONG_VERT,
		nullptr,
		nullptr,
		nullptr,
		PATH_SUFFIX SHADER_PATH BLINN_PHONG_FRAG,
	};

	OwningPointer<EffectComponent> effect = OwningPointer<EffectComponent>::Create(effect);
	effect->owner = Entity::Query(this).p;
	effect->RegisterShaderPath(shaderpaths);
	effect->SetTexture(teapottexture);
	effect->SetTexture(teapottexture2);
	effect->SetTexture(teapottexture3);
	Entity::RegisterEffectComponent(effect);
}

inline void Teapot::Init()
{
	PremadeObjebct::Init();
}

inline void Teapot::Update(float i_dt)
{
	PremadeObjebct::Update(i_dt);
}