#pragma once

#include <Core/Math/Vector.h>
#include <PremadeParts/PremadeObject.h>

#include <Graphics/SceneEntity.h>

class Teapot : public PremadeObjebct
{
	void Boot() override;
	void Init() override;
	void Update(float i_dt) override;
};

inline void Teapot::Boot()
{
	PremadeObjebct::Boot();

	SceneFormat* format = SceneEntity::Query(this);
	format->proxy->mesh->Load("../../Assets/models/teapot.obj");

	TextureAttribute * teapottexture = new TextureAttribute();
	teapottexture->Load("../../Assets/textures/brickwall.png");
	TextureAttribute * teapottexture2 = new TextureAttribute();
	teapottexture2->Load("../../Assets/textures/brickwall.png");
	TextureAttribute* teapottexture3 = new TextureAttribute();
	teapottexture3->Load("../../Assets/textures/brickwall_normal.png");
	format->proxy->mesh->SetTexture(teapottexture);
	format->proxy->mesh->SetTexture(teapottexture2);
	format->proxy->mesh->SetTexture(teapottexture3);

	Shader * teapotshader = new Shader(PATH_SUFFIX SHADER_PATH BLINN_PHONG_VERT, PATH_SUFFIX SHADER_PATH BLINN_PHONG_FRAG);
	format->AddShader(teapotshader);
}

inline void Teapot::Init()
{
	PremadeObjebct::Init();
	this->pos = Vec3f(0, 0, -50);
	this->rot = Vec3f(-90, 0, 0);
	this->scale = Vec3f(1.0, 1.0, 1.0);
}

inline void Teapot::Update(float i_dt)
{
	PremadeObjebct::Update(i_dt);
}