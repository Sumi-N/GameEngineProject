#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

namespace Tempest
{

	class AnimatedPlayer : public PremadeObjebct
	{
	public:
		AnimatedPlayer() : albedo(), metalic(), roughness() {}

		void Boot() override;
		void Init() override;
		void Update(float i_dt) override;

		void ChangePos(const Vec3f& i_pos);
		void ChangeMaterialParameter(float i_metalic, float i_roughness);

		Vec4f albedo;
		float metalic;
		float roughness;
	};

	inline void AnimatedPlayer::Boot()
	{
		PremadeObjebct::Boot();

		Owner<TextureAttribute> albedo = Owner<TextureAttribute>::Create(albedo);
		Owner<TextureAttribute> normal = Owner<TextureAttribute>::Create(normal);
		Owner<TextureAttribute> roughness = Owner<TextureAttribute>::Create(roughness);
		Owner<TextureAttribute> metalic = Owner<TextureAttribute>::Create(metalic);

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

		albedo->Load   (PATH_SUFFIX BIN_TEXTURE_PATH "albedo/gold-scuffed_basecolor.tt",    TextureType::Albedo);
		normal->Load   (PATH_SUFFIX BIN_TEXTURE_PATH "normal/gold-scuffed_normal.tt",       TextureType::Normal);
		roughness->Load(PATH_SUFFIX BIN_TEXTURE_PATH "roughness/gold-scuffed_roughness.tt", TextureType::Roughness);
		metalic->Load  (PATH_SUFFIX BIN_TEXTURE_PATH "metallic/gold-scuffed_metalic.tt",  TextureType::Metalic);
		
		effect_component->SetTexture(albedo);


		effect_component->SetTexture(normal);
		effect_component->SetTexture(roughness);
		effect_component->SetTexture(metalic);
		
		mesh_component->Load(PATH_SUFFIX BIN_MESH_PATH "xbot.tsm");

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

		effect_component->material_attribute->material->albedo = Vec4f(1.0, 0, 0, 1.0);

		effect_component->material_attribute->material->metalic = metalic;
		effect_component->material_attribute->material->roughness = roughness;
	}

	inline void AnimatedPlayer::Update(float i_dt)
	{
		PremadeObjebct::Update(i_dt);
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