#pragma once
#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

class WornPaintedCement : public Sphere
{
public:
	void Boot() override;
	void Init() override;
};

inline void WornPaintedCement::Boot()
{
	Sphere::Boot();

	OwningPointer<TextureAttribute> albedo = OwningPointer<TextureAttribute>::Create(albedo);
	OwningPointer<TextureAttribute> normal = OwningPointer<TextureAttribute>::Create(normal);
	OwningPointer<TextureAttribute> roughness = OwningPointer<TextureAttribute>::Create(roughness);
	OwningPointer<TextureAttribute> metalic = OwningPointer<TextureAttribute>::Create(metalic);

	albedo->Load(PATH_SUFFIX TEXTURE_PATH WARN_PAINTED_CEMENT_ALBEDO, TextureType::Albedo);
	normal->Load(PATH_SUFFIX TEXTURE_PATH WARN_PAINTED_CEMENT_NORMAL, TextureType::Normal);
	roughness->Load(PATH_SUFFIX TEXTURE_PATH WARN_PAINTED_CEMENT_ROUGHNESS, TextureType::Roughness);
	metalic->Load(PATH_SUFFIX TEXTURE_PATH WARN_PAINTED_CEMENT_METALIC, TextureType::Metalic);
	
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

inline void WornPaintedCement::Init()
{
	Sphere::Init();
}