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

		albedo->Load(PATH_SUFFIX TEXTURE_PATH "albedo/old-soiled-cloth1-albedo.png", TextureType::Albedo);
		normal->Load(PATH_SUFFIX TEXTURE_PATH "normal/old-soiled-cloth1-Normal-dx.png", TextureType::Normal);
		roughness->Load(PATH_SUFFIX TEXTURE_PATH "roughness/old-soiled-cloth1-Roughness.png", TextureType::Roughness);
		metalic->Load(PATH_SUFFIX TEXTURE_PATH "metallic/old-soiled-cloth1-Metallic.png", TextureType::Metalic);

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

	inline void OldSoiledClothSphere::Init()
	{
		Sphere::Init();
	}

}
