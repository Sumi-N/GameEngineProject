#pragma once

#include "Define.h"
#include "Attribute.h"

namespace Tempest
{

	class MaterialAttribute : public Attribute
	{
	public:
		MaterialAttribute();

		OwningPointer<Resource::Material> material;
				
		void SetMaterialValue(Vec4f i_albedo, float roughness, float metalic);
	};

	inline MaterialAttribute::MaterialAttribute() 
	{
		material = OwningPointer<Resource::Material>::Create(material);
		material->albedo    = Vec4f(0.50980395f, 0.0, 0.0, 1.0f);
		material->roughness = 1.0f;
		material->metalic   = 1.0f;
	}	

	inline void MaterialAttribute::SetMaterialValue(Vec4f i_albedo, float i_roughness, float i_metalic)
	{
		material->albedo = i_albedo;
		material->roughness = i_roughness;
		material->metalic = i_metalic;
	}

}

