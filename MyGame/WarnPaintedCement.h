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

		TextureAttribute albedo;
		TextureAttribute normal;
		TextureAttribute roughness;
		TextureAttribute metalic;

		albedo.Load(PATH_SUFFIX BIN_TEXTURE_PATH "albedo\\wornpaintedcement-albedo.tt", TextureType::Albedo);
		normal.Load(PATH_SUFFIX BIN_TEXTURE_PATH "normal\\wornpaintedcement-normal.tt", TextureType::Normal);
		roughness.Load(PATH_SUFFIX BIN_TEXTURE_PATH "roughness\\wornpaintedcement-roughness.tt", TextureType::Roughness);
		metalic.Load(PATH_SUFFIX BIN_TEXTURE_PATH "metallic\\wornpaintedcement-metalness.tt", TextureType::Metalic);		
		
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

	inline void WornPaintedCement::Init()
	{
		Sphere::Init();
	}

}