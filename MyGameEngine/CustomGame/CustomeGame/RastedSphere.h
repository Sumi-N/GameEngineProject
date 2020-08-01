#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

class RastedSphere : public Sphere
{
public:
	void Boot() override;
	void Init() override;
	void Update(float) override;
};

inline void RastedSphere::Boot()
{
	RastedSphere();
	Sphere::Boot();

	OwningPointer<TextureAttribute> albedo = ObjectFactory<TextureAttribute>::Create();
	OwningPointer<TextureAttribute> normal = ObjectFactory<TextureAttribute>::Create();
	OwningPointer<TextureAttribute> roughness = ObjectFactory<TextureAttribute>::Create();
	OwningPointer<TextureAttribute> metalic = ObjectFactory<TextureAttribute>::Create();

	albedo->Load(PATH_SUFFIX TEXTURE_PATH RUSTED_IRON_ALBEDO, TextureType::Albedo);
	normal->Load(PATH_SUFFIX TEXTURE_PATH RUSTED_IRON_NORMAL, TextureType::Normal);
	roughness->Load(PATH_SUFFIX TEXTURE_PATH RUSTED_IRON_ROUGHNESS, TextureType::Roughness);
	metalic->Load(PATH_SUFFIX TEXTURE_PATH RUSTED_IRON_METALIC, TextureType::Metalic);

	const char* shaderpaths[] =
	{
		PATH_SUFFIX SHADER_PATH DISNEY_PBR_VERT,
		nullptr,
		nullptr,
		nullptr,
		PATH_SUFFIX SHADER_PATH DISNEY_PBR_FRAG,
	};

	OwningPointer<EffectComponent> effect = ObjectFactory<EffectComponent>::Create();
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

inline void RastedSphere::Update(float i_dt)
{
	//int total = 0;
	//for (int i = 0; i < 10000000; i++)
	//{
	//	total += i;
	//}
}