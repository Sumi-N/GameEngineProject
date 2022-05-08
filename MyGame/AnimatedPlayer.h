#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

namespace Tempest
{

	class AnimatedPlayer : public PremadeObjebct
	{
	public:
		void Boot() override;
		void Init() override;
		void Update(float i_dt) override;

		void ChangePos(const Vec3f& i_pos);				
	};

	inline void AnimatedPlayer::Boot()
	{
		PremadeObjebct::Boot();

		name = "Animated Player";

		const char* shaderpaths[] =
		{
			//PATH_SUFFIX SHADER_PATH PBR_ANIMATION_VERT,
			PATH_SUFFIX SHADER_PATH DEBUG_PBR_ANIMATION_VERT,
			nullptr,
			nullptr,
			nullptr,
			//PATH_SUFFIX SHADER_PATH PBR_ANIMATION_FRAG,
			PATH_SUFFIX SHADER_PATH DEBUG_PBR_ANIMATION_FRAG,
		};

		effect_component->RegisterShaderPath(shaderpaths);				
		effect_component->RegisterTexture(TextureType::Albedo, PATH_SUFFIX BIN_TEXTURE_PATH "albedo/gold-scuffed_basecolor.tt");
		effect_component->RegisterTexture(TextureType::Normal, PATH_SUFFIX BIN_TEXTURE_PATH "normal/gold-scuffed_normal.tt");
		effect_component->RegisterTexture(TextureType::Roughness, PATH_SUFFIX BIN_TEXTURE_PATH "roughness/gold-scuffed_roughness.tt");
		effect_component->RegisterTexture(TextureType::Metalic, PATH_SUFFIX BIN_TEXTURE_PATH "metallic/gold-scuffed_metalic.tt");
		
		mesh_component->RegisterMesh(PATH_SUFFIX BIN_MESH_PATH "xbot.tsm");

		Owner<AnimationComponent> animation_component = Owner<AnimationComponent>::Create(animation_component);
		animation_component->owner = Entity::Query(this);
		animation_component->mesh = mesh_component;		
		animation_component->LoadSkeleton(PATH_SUFFIX BIN_MESH_PATH "xbot.ts");
		animation_component->LoadClip(PATH_SUFFIX BIN_MESH_PATH "RumbaDancing.tac");
		Entity::RegisterAnimationComponent(animation_component);		
	}

	inline void AnimatedPlayer::Init()
	{
		PremadeObjebct::Init();			
	}

	inline void AnimatedPlayer::Update(float i_dt)
	{
		PremadeObjebct::Update(i_dt);
	}

	inline void AnimatedPlayer::ChangePos(const Vec3f& i_pos)
	{
		pos = i_pos;
	}
}