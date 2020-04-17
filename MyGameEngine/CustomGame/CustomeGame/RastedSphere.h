#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

class RastedSphere : public Sphere
{
public:
	void Boot() override;
	void Init() override;

	Vec4f albedo;
	float metalic;
	float roughness;
};

inline void RastedSphere::Boot()
{
	Sphere::Boot();

	TextureAttribute* albedo = new TextureAttribute();
	albedo->Load(PATH_SUFFIX TEXTURE_PATH RUSTED_IRON_ALBEDO, TextureType::Albedo);
	TextureAttribute* normal = new TextureAttribute();
	normal->Load(PATH_SUFFIX TEXTURE_PATH RUSTED_IRON_NORMAL, TextureType::Normal);
	TextureAttribute* roughness = new TextureAttribute();
	roughness->Load(PATH_SUFFIX TEXTURE_PATH RUSTED_IRON_ROUGHNESS, TextureType::Roughness);
	TextureAttribute* metalic = new TextureAttribute();
	metalic->Load(PATH_SUFFIX TEXTURE_PATH RUSTED_IRON_METALIC, TextureType::Metalic);

	const char* shaderpaths[] =
	{
		PATH_SUFFIX SHADER_PATH DISNEY_PBR_VERT,
		nullptr,
		nullptr,
		nullptr,
		PATH_SUFFIX SHADER_PATH DISNEY_PBR_FRAG,
	};

	EffectComponent* effect = new EffectComponent();
	effect->owner = Entity::Query(this).p;
	effect->RegisterShaderPath(shaderpaths);
	effect->SetTexture(albedo);
	effect->SetTexture(normal);
	effect->SetTexture(roughness);
	effect->SetTexture(metalic);
	Entity::RegisterEffectComponent(effect);
}

inline void RastedSphere::Init()
{
	Sphere::Init();
}