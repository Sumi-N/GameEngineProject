#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

class SpherePBR_Test : public Sphere
{
public:
	void Init() override;
	void ChangePos(Vec3f i_pos);
	void ChangeMaterialParameter(float i_metalic, float i_roughness);

	Vec4f albedo;
	float metalic;
	float roughness;
};

inline void SpherePBR_Test::Init()
{
	Sphere::Init();
	
	SceneFormat* format = SceneEntity::Query(this);
	format->proxy->mesh->material->albedo = Vec4f(1.0, 0, 0, 1.0);

	format->proxy->mesh->material->metalic = metalic;
	format->proxy->mesh->material->roughness = roughness;
}

inline void SpherePBR_Test::ChangePos(Vec3f i_pos)
{
	pos = i_pos;
}

inline void SpherePBR_Test::ChangeMaterialParameter(float i_metalic, float i_roughness)
{
	metalic = i_metalic;
	roughness = i_roughness;
}