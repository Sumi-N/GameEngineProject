#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

namespace Tempest
{

	class BrushedMetalSphere : public Sphere
	{
	public:
		void Boot() override;
		void Init() override;
	};

	inline void BrushedMetalSphere::Boot()
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
		effect_component->RegisterTexture(Resource::TextureType::Albedo, PATH_SUFFIX BIN_TEXTURE_PATH "albedo/brushed-metal_albedo.tt");
		effect_component->RegisterTexture(Resource::TextureType::Normal, PATH_SUFFIX BIN_TEXTURE_PATH "normal/brushed-metal_normal-dx.tt");
		effect_component->RegisterTexture(Resource::TextureType::Roughness, PATH_SUFFIX BIN_TEXTURE_PATH "roughness/brushed-metal_roughness.tt");
		effect_component->RegisterTexture(Resource::TextureType::Metalic, PATH_SUFFIX BIN_TEXTURE_PATH "metallic/brushed-metal_metallic.tt");
	}

	inline void BrushedMetalSphere::Init()
	{
		Sphere::Init();
	}

}