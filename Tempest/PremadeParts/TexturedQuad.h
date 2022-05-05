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

		TextureAttribute texture;
		texture.Load(PATH_SUFFIX BIN_TEXTURE_PATH "albedo\\brickwall.ttd", TextureType::PB_Diffuse);
		TextureAttribute texture2;
		texture2.Load(PATH_SUFFIX BIN_TEXTURE_PATH "albedo\\brickwall.ttd", TextureType::PB_Specular);

		OwningPointer<EffectComponent> effect = OwningPointer<EffectComponent>::Create(effect);
		effect->owner = Entity::Query(this);
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