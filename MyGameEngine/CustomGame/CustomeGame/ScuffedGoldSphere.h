#pragma once
#pragma once

#include <core/Math//Vector.h>
#include <PremadeParts/Sphere.h>

class ScuffedGoldSphere : public Sphere
{
public:
	void Boot() override;
	void Init() override;

	Vec4f albedo;
	float metalic;
	float roughness;
};

inline void ScuffedGoldSphere::Boot()
{
	Sphere::Boot();

	SceneFormat* format = SceneEntity::Query(this);

	TextureAttribute* albedo = new TextureAttribute();
	albedo->Load(PATH_SUFFIX TEXTURE_PATH GOLD_SCUFFED_BOOSTED_ALBEDO, TextureType::Albedo);
	TextureAttribute* normal = new TextureAttribute();
	normal->Load(PATH_SUFFIX TEXTURE_PATH GOLD_SCUFFED_NORMAL, TextureType::Normal);
	TextureAttribute* roughness = new TextureAttribute();
	roughness->Load(PATH_SUFFIX TEXTURE_PATH GOLD_SCUFFED_ROUGHNESS, TextureType::Roughness);
	TextureAttribute* metalic = new TextureAttribute();
	metalic->Load(PATH_SUFFIX TEXTURE_PATH GOLD_SCUFFED_METALIC, TextureType::Metalic);

	format->proxy->mesh->SetTexture(albedo);
	format->proxy->mesh->SetTexture(normal);
	format->proxy->mesh->SetTexture(roughness);
	format->proxy->mesh->SetTexture(metalic);

	Shader* shader = new Shader(PATH_SUFFIX SHADER_PATH DISNEY_PBR_VERT, PATH_SUFFIX SHADER_PATH DISNEY_PBR_FRAG);
	format->ReplaceShader(shader);
}

inline void ScuffedGoldSphere::Init()
{
	Sphere::Init();
}