#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

namespace Tempest
{

	class MetalGridSphere : public Sphere
	{
	public:
		void Boot() override;
		void Init() override;
	};

	inline void MetalGridSphere::Boot()
	{
		Sphere::Boot();

		OwningPointer<TextureAttribute> albedo = OwningPointer<TextureAttribute>::Create(albedo);
		OwningPointer<TextureAttribute> normal = OwningPointer<TextureAttribute>::Create(normal);
		OwningPointer<TextureAttribute> roughness = OwningPointer<TextureAttribute>::Create(roughness);
		OwningPointer<TextureAttribute> metalic = OwningPointer<TextureAttribute>::Create(metalic);

		albedo->Load(PATH_SUFFIX BIN_TEXTURE_PATH "albedo/metalgrid1_basecolor.tt", TextureType::Albedo);
		normal->Load(PATH_SUFFIX BIN_TEXTURE_PATH "normal/metalgrid1_normal-ogl.tt", TextureType::Normal);
		roughness->Load(PATH_SUFFIX BIN_TEXTURE_PATH "roughness/metalgrid1_roughness.tt", TextureType::Roughness);
		metalic->Load(PATH_SUFFIX BIN_TEXTURE_PATH "metallic/metalgrid1_metallic.tt", TextureType::Metalic);

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

	inline void MetalGridSphere::Init()
	{
		Sphere::Init();
	}

}