#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

class BrushedMetalSphere : public Sphere
{
public:
	void Boot() override;
	void Init() override;
};

inline void BrushedMetalSphere::Boot()
{
	Sphere::Boot();

	OwningPointer<TextureAttribute> albedo = OwningPointer<TextureAttribute>::Create(albedo);
	OwningPointer<TextureAttribute> normal = OwningPointer<TextureAttribute>::Create(normal);
	OwningPointer<TextureAttribute> roughness = OwningPointer<TextureAttribute>::Create(roughness);
	OwningPointer<TextureAttribute> metalic = OwningPointer<TextureAttribute>::Create(metalic);

	albedo->Load(PATH_SUFFIX TEXTURE_PATH "albedo/brushed-metal_albedo.png", TextureType::Albedo);
	normal->Load(PATH_SUFFIX TEXTURE_PATH "normal/brushed-metal_normal-dx.png", TextureType::Normal);
	roughness->Load(PATH_SUFFIX TEXTURE_PATH "roughness/brushed-metal_roughness.png", TextureType::Roughness);
	metalic->Load(PATH_SUFFIX TEXTURE_PATH "metallic/brushed-metal_metallic.png", TextureType::Metalic);

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

inline void BrushedMetalSphere::Init()
{
	Sphere::Init();
}
