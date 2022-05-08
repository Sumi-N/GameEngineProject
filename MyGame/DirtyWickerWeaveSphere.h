#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

namespace Tempest
{

	class DirtyWickerWeaveSphere : public Sphere
	{
	public:
		void Boot() override;
		void Init() override;
	};

	inline void DirtyWickerWeaveSphere::Boot()
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
		effect_component->RegisterTexture(TextureType::Albedo, PATH_SUFFIX BIN_TEXTURE_PATH "albedo/dirty-wicker-weave1-albedo.tt");
		effect_component->RegisterTexture(TextureType::Normal, PATH_SUFFIX BIN_TEXTURE_PATH "normal/dirty-wicker-weave1-normal-dx.tt");
		effect_component->RegisterTexture(TextureType::Roughness, PATH_SUFFIX BIN_TEXTURE_PATH "roughness/dirty-wicker-weave1-roughness.tt");
		effect_component->RegisterTexture(TextureType::Metalic, PATH_SUFFIX BIN_TEXTURE_PATH "metallic/dirty-wicker-weave1-metallic.tt");
	}

	inline void DirtyWickerWeaveSphere::Init()
	{
		Sphere::Init();
	}

}