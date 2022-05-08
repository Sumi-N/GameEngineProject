#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

namespace Tempest
{

	class BathRoomTileSphere : public Sphere
	{
	public:
		void Boot() override;
		void Init() override;
	};

	inline void BathRoomTileSphere::Boot()
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
		effect_component->RegisterTexture(TextureType::Albedo, PATH_SUFFIX BIN_TEXTURE_PATH "albedo/bathroomtile1_basecolor.tt");
		effect_component->RegisterTexture(TextureType::Normal, PATH_SUFFIX BIN_TEXTURE_PATH "normal/bathroomtile1_normal-dx.tt");
		effect_component->RegisterTexture(TextureType::Roughness, PATH_SUFFIX BIN_TEXTURE_PATH "roughness/bathroomtile1_roughness.tt");
		effect_component->RegisterTexture(TextureType::Metalic, PATH_SUFFIX BIN_TEXTURE_PATH "metallic/bathroomtile1_metalness.tt");
	}

	inline void BathRoomTileSphere::Init()
	{
		Sphere::Init();
	}

}
