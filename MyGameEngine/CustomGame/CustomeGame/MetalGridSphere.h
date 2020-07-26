#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

class MetalGridSphere : public Sphere
{
public:
	void Boot() override;
	void Init() override;
};

inline void MetalGridSphere::Boot()
{
	Sphere::Boot();

	TextureAttribute* albedo = new TextureAttribute();
	albedo->Load(PATH_SUFFIX TEXTURE_PATH "albedo/metalgrid1_basecolor.png", TextureType::Albedo);
	TextureAttribute* normal = new TextureAttribute();
	normal->Load(PATH_SUFFIX TEXTURE_PATH "normal/metalgrid1_normal-ogl.png", TextureType::Normal);
	TextureAttribute* roughness = new TextureAttribute();
	roughness->Load(PATH_SUFFIX TEXTURE_PATH "roughness/metalgrid1_roughness.png", TextureType::Roughness);
	TextureAttribute* metalic = new TextureAttribute();
	metalic->Load(PATH_SUFFIX TEXTURE_PATH "metallic/metalgrid1_metallic.png", TextureType::Metalic);

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

inline void MetalGridSphere::Init()
{
	Sphere::Init();
}
