#pragma once

#pragma once

#include "Define.h"
#include "Quad.h"

class TexturedQuad : public Quad
{
public:
	void Boot() override;
	void Init() override;
};

inline void TexturedQuad::Boot()
{
	Quad::Boot();

	SceneFormat* format = SceneEntity::Query(this);

	TextureAttribute* texture = new TextureAttribute();
	texture->Load("../../Assets/textures/albedo/brickwall.png", TextureType::PB_Diffuse);
	TextureAttribute* texture2 = new TextureAttribute();
	texture2->Load("../../Assets/textures/albedo/brickwall.png", TextureType::PB_Specular);
	format->proxy->mesh->SetTexture(texture);
	format->proxy->mesh->SetTexture(texture2);

	Shader* quadshader = new Shader(PATH_SUFFIX SHADER_PATH BLINN_PHONG_VERT, PATH_SUFFIX SHADER_PATH BLINN_PHONG_FRAG);
	format->ReplaceShader(quadshader);
}

inline void TexturedQuad::Init()
{
	Quad::Init();
}