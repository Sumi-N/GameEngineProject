#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

class BathRoomTileSphere : public Sphere
{
public:
	void Boot() override;
	void Init() override;
};

inline void BathRoomTileSphere::Boot()
{
	Sphere::Boot();

	OwningPointer<TextureAttribute> albedo    = OwningPointer<TextureAttribute>::Create(albedo);
	OwningPointer<TextureAttribute> normal    = OwningPointer<TextureAttribute>::Create(normal);
	OwningPointer<TextureAttribute> roughness = OwningPointer<TextureAttribute>::Create(roughness);
	OwningPointer<TextureAttribute> metalic   = OwningPointer<TextureAttribute>::Create(metalic);

	albedo->Load(PATH_SUFFIX TEXTURE_PATH "albedo/bathroomtile1_basecolor.png", TextureType::Albedo);
	normal->Load(PATH_SUFFIX TEXTURE_PATH "normal/bathroomtile1_normal-dx.png", TextureType::Normal);
	roughness->Load(PATH_SUFFIX TEXTURE_PATH "roughness/bathroomtile1_roughness.png", TextureType::Roughness);
	metalic->Load(PATH_SUFFIX TEXTURE_PATH "metallic/bathroomtile1_metalness.png", TextureType::Metalic);

	const char* shaderpaths[] =
	{
		PATH_SUFFIX SHADER_PATH DISNEY_PBR_VERT,
		nullptr,
		nullptr,
		nullptr,
		PATH_SUFFIX SHADER_PATH DISNEY_PBR_FRAG,
	};

	OwningPointer<EffectComponent> effect = OwningPointer<EffectComponent>::Create(effect);
	effect->owner = Entity::Query(this).p;
	effect->RegisterShaderPath(shaderpaths);
	effect->SetTexture(albedo);
	effect->SetTexture(normal);
	effect->SetTexture(roughness);
	effect->SetTexture(metalic);
	Entity::RegisterEffectComponent(effect);
}

inline void BathRoomTileSphere::Init()
{
	Sphere::Init();
}
