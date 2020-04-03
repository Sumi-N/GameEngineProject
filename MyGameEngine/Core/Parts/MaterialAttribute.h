#pragma once

#include "Define.h"
#include "Attribute.h"

class MaterialAttribute : public Attribute
{
public:
	MaterialAttribute();

	// Ambient, Diffuse, Specular
	Vec3f Ka, Kd, Ks;
	// Specular exponent
	float Ns;

	Vec4f albedo;
	float roughness, metalic;

	void SetMaterialValue(Vec3f, float);
	void SetMaterialValue(Vec4f i_albedo, float roughness, float metalic);
};

inline MaterialAttribute::MaterialAttribute()
{
	Ka = Vec3f(0.50980395f, 0.0, 0.0);
	Kd = Vec3f(0.50980395f, 0.0, 0.0);
	Ks = Vec3f(0.80099994f, 0.80099994f, 0.80099994f);
	Ns = 10.0f;
}

inline void MaterialAttribute::SetMaterialValue(Vec3f i_values, float i_specular)
{
	Ka = i_values;
	Kd = i_values;
	Ks = i_values;
	Ns = i_specular;
}

inline void MaterialAttribute::SetMaterialValue(Vec4f i_albedo, float i_roughness, float i_metalic)
{
	albedo = i_albedo;
	roughness = i_roughness;
	metalic = i_metalic;
}

