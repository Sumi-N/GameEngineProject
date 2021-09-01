#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

namespace Tempest
{

	class AnimatedPlayer : public PremadeObjebct
	{
	public:
		AnimatedPlayer() : albedo(), metalic(), roughness()
		{
		}

		void Boot() override;
		void Init() override;
		void ChangePos(const Vec3f& i_pos);
		void ChangeMaterialParameter(float i_metalic, float i_roughness);

		Vec4f albedo;
		float metalic;
		float roughness;
	};

	inline void AnimatedPlayer::Boot()
	{
		PremadeObjebct::Boot();

		const char* shaderpaths[] =
		{
			PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_VERT,
			nullptr,
			nullptr,
			nullptr,
			PATH_SUFFIX SHADER_PATH DEBUG_PBR_BASIC_FRAG,
		};

		mesh_component->Load(PATH_SUFFIX BIN_MESH_PATH "SK_PlayerCharacter.tmd");

		OwningPointer<EffectComponent> effect = OwningPointer<EffectComponent>::Create(effect);
		effect->owner = Entity::Query(this).p;
		effect->RegisterShaderPath(shaderpaths);
		Entity::RegisterEffectComponent(effect);
	}

	inline void AnimatedPlayer::Init()
	{
		PremadeObjebct::Init();

		mesh_component->material_attribute->material->albedo = Vec4f(1.0, 0, 0, 1.0);

		mesh_component->material_attribute->material->metalic = metalic;
		mesh_component->material_attribute->material->roughness = roughness;
	}

	inline void AnimatedPlayer::ChangePos(const Vec3f& i_pos)
	{
		pos = i_pos;
	}

	inline void AnimatedPlayer::ChangeMaterialParameter(float i_metalic, float i_roughness)
	{
		metalic = i_metalic;
		roughness = i_roughness;
	}

}