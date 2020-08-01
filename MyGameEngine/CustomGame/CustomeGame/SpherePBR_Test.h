#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

class SpherePBR_Test : public Sphere
{
public:
	SpherePBR_Test(): albedo(), metalic(), roughness() {}

	void Boot() override;
	void Init() override;
	void ChangePos(const Vec3f& i_pos);
	void ChangeMaterialParameter(float i_metalic, float i_roughness);

	Vec4f albedo;
	float metalic;
	float roughness;
};

inline void SpherePBR_Test::Boot()
{
	Sphere::Boot();

	const char* shaderpaths[] =
	{
		PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_VERT,
		nullptr,
		nullptr,
		nullptr,
		PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_FRAG,
	};

	OwningPointer<EffectComponent> effect = ObjectFactory<EffectComponent>::Create();
	effect->owner = Entity::Query(this).p;
	effect->RegisterShaderPath(shaderpaths);
	Entity::RegisterEffectComponent(effect);
}

inline void SpherePBR_Test::Init()
{
	Sphere::Init();
	
	mesh->material->albedo = Vec4f(1.0, 0, 0, 1.0);

	mesh->material->metalic = metalic;
	mesh->material->roughness = roughness;
}

inline void SpherePBR_Test::ChangePos(const Vec3f& i_pos)
{
	pos = i_pos;
}

inline void SpherePBR_Test::ChangeMaterialParameter(float i_metalic, float i_roughness)
{
	metalic = i_metalic;
	roughness = i_roughness;
}