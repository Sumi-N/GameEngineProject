#pragma once
#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

namespace Tempest
{

	class WornPaintedCement : public Sphere
	{
	public:
		void Boot() override;
		void Init() override;
	};

	inline void WornPaintedCement::Boot()
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
		effect_component->RegisterTexture(TextureType::Albedo, PATH_SUFFIX BIN_TEXTURE_PATH "albedo/wornpaintedcement-albedo.tt");
		effect_component->RegisterTexture(TextureType::Normal, PATH_SUFFIX BIN_TEXTURE_PATH "normal/wornpaintedcement-normal.tt");
		effect_component->RegisterTexture(TextureType::Roughness, PATH_SUFFIX BIN_TEXTURE_PATH "roughness/wornpaintedcement-roughness.tt");
		effect_component->RegisterTexture(TextureType::Metalic, PATH_SUFFIX BIN_TEXTURE_PATH "metallic//wornpaintedcement-metalness.tt");
	}

	inline void WornPaintedCement::Init()
	{
		Sphere::Init();
	}

}