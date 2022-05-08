#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

namespace Tempest
{

	class OldSoiledClothSphere : public Sphere
	{
	public:
		void Boot() override;
		void Init() override;
	};

	inline void OldSoiledClothSphere::Boot()
	{
		Sphere::Boot();		

		const char* shaderpaths[] =
		{
			PATH_SUFFIX SHADER_PATH DISNEY_PBR_VERT,
			nullptr,
			nullptr,
			nullptr,
			PATH_SUFFIX SHADER_PATH DISNEY_PBR_FRAG,
		};

		effect_component->RegisterShaderPath(shaderpaths);
		effect_component->RegisterTexture(TextureType::Albedo, PATH_SUFFIX BIN_TEXTURE_PATH "albedo/old-soiled-cloth1-albedo.tt");
		effect_component->RegisterTexture(TextureType::Normal, PATH_SUFFIX BIN_TEXTURE_PATH "normal/old-soiled-cloth1-Normal-dx.tt");
		effect_component->RegisterTexture(TextureType::Roughness, PATH_SUFFIX BIN_TEXTURE_PATH "roughness/old-soiled-cloth1-Roughness.tt");
		effect_component->RegisterTexture(TextureType::Metalic, PATH_SUFFIX BIN_TEXTURE_PATH "metallic/old-soiled-cloth1-Metallic.tt");
	}

	inline void OldSoiledClothSphere::Init()
	{
		Sphere::Init();
	}

}
