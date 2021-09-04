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

		OwningPointer<TextureAttribute> albedo = OwningPointer<TextureAttribute>::Create(albedo);
		OwningPointer<TextureAttribute> normal = OwningPointer<TextureAttribute>::Create(normal);
		OwningPointer<TextureAttribute> roughness = OwningPointer<TextureAttribute>::Create(roughness);
		OwningPointer<TextureAttribute> metalic = OwningPointer<TextureAttribute>::Create(metalic);

		albedo->Load(PATH_SUFFIX BIN_TEXTURE_PATH "albedo/old-soiled-cloth1-albedo.ttd", TextureType::Albedo);
		normal->Load(PATH_SUFFIX BIN_TEXTURE_PATH "normal/old-soiled-cloth1-Normal-dx.ttd", TextureType::Normal);
		roughness->Load(PATH_SUFFIX BIN_TEXTURE_PATH "roughness/old-soiled-cloth1-Roughness.ttd", TextureType::Roughness);
		metalic->Load(PATH_SUFFIX BIN_TEXTURE_PATH "metallic/old-soiled-cloth1-Metallic.ttd", TextureType::Metalic);

		const char* shaderpaths[] =
		{
			PATH_SUFFIX SHADER_PATH DISNEY_PBR_VERT,
			nullptr,
			nullptr,
			nullptr,
			PATH_SUFFIX SHADER_PATH DISNEY_PBR_FRAG,
		};

		effect_component->RegisterShaderPath(shaderpaths);
		effect_component->SetTexture(albedo);
		effect_component->SetTexture(normal);
		effect_component->SetTexture(roughness);
		effect_component->SetTexture(metalic);
	}

	inline void OldSoiledClothSphere::Init()
	{
		Sphere::Init();
	}

}
