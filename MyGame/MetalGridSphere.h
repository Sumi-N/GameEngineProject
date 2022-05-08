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

		const char* shaderpaths[] =
		{
			PATH_SUFFIX SHADER_PATH DISNEY_PBR_VERT,
			nullptr,
			nullptr,
			nullptr,
			PATH_SUFFIX SHADER_PATH DISNEY_PBR_FRAG,
		};

		effect_component->RegisterShaderPath(shaderpaths);
		effect_component->RegisterTexture(TextureType::Albedo, PATH_SUFFIX BIN_TEXTURE_PATH "albedo/metalgrid1_basecolor.tt");
		effect_component->RegisterTexture(TextureType::Normal, PATH_SUFFIX BIN_TEXTURE_PATH "normal/metalgrid1_normal-ogl.tt");
		effect_component->RegisterTexture(TextureType::Roughness, PATH_SUFFIX BIN_TEXTURE_PATH "roughness/metalgrid1_roughness.tt");
		effect_component->RegisterTexture(TextureType::Metalic, PATH_SUFFIX BIN_TEXTURE_PATH "metallic/metalgrid1_metallic.tt");
	}

	inline void MetalGridSphere::Init()
	{
		Sphere::Init();
	}

}