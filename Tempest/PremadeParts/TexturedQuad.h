#pragma once

#include "Define.h"
#include "Quad.h"

namespace Tempest
{

	class TexturedQuad : public Quad
	{
	public:
		void Boot() override;
		void Init() override;
	};

	inline void TexturedQuad::Boot()
	{
		Quad::Boot();

		const char* shaderpaths[] =
		{
			PATH_SUFFIX SHADER_PATH BLINN_PHONG_VERT,
			nullptr,
			nullptr,
			nullptr,
			PATH_SUFFIX SHADER_PATH BLINN_PHONG_FRAG,
		};

		TextureAttribute* texture = new TextureAttribute();
		texture->Load(PATH_SUFFIX "Assets/textures/albedo/brickwall.png", TextureType::PB_Diffuse);
		TextureAttribute* texture2 = new TextureAttribute();
		texture2->Load(PATH_SUFFIX "Assets/textures/albedo/brickwall.png", TextureType::PB_Specular);

		OwningPointer<EffectComponent> effect = OwningPointer<EffectComponent>::Create(effect);
		effect->owner = Entity::Query(this).p;
		effect->RegisterShaderPath(shaderpaths);
		effect->SetTexture(texture);
		effect->SetTexture(texture2);
		Entity::RegisterEffectComponent(effect);
	}

	inline void TexturedQuad::Init()
	{
		Quad::Init();
	}

}