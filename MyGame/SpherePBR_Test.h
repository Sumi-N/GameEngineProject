#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

namespace Tempest
{

	class SpherePBR_Test : public Sphere
	{
	public:
		SpherePBR_Test() : albedo(), metalic(), roughness()
		{
		}

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
		effect_component->RegisterShaderPath(shaderpaths);
	}

	inline void SpherePBR_Test::Init()
	{
		Sphere::Init();

		effect_component->material_attribute->material->albedo = Vec4f(1.0, 0, 0, 1.0);
		effect_component->material_attribute->material->metalic = metalic;
		effect_component->material_attribute->material->roughness = roughness;
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

}