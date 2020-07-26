#pragma once

#include "Define.h"
#include "Component.h"
#include "TextureAttribute.h"

class EffectComponent : public Component
{
public:
	EffectComponent();

	ObservingPointer<Object> owner;
	const char* shaderpaths[5];
	std::vector<OwningPointer<TextureAttribute>> textures;

	void RegisterShaderPath(const char**);
	void SetTexture(TextureAttribute*);
	void ReplaceTexture(TextureAttribute*, int);
};

inline EffectComponent::EffectComponent(): shaderpaths() {}

inline void EffectComponent::RegisterShaderPath(const char ** shaderpaths)
{
	this->shaderpaths[0] = shaderpaths[0];
	this->shaderpaths[1] = shaderpaths[1];
	this->shaderpaths[2] = shaderpaths[2];
	this->shaderpaths[3] = shaderpaths[3];
	this->shaderpaths[4] = shaderpaths[4];
}

inline void EffectComponent::SetTexture(TextureAttribute* i_texture)
{
	OwningPointer<TextureAttribute> texturehandler;
	texturehandler = i_texture;
	textures.push_back(texturehandler);
}

inline void EffectComponent::ReplaceTexture(TextureAttribute* i_texture, int ith_item = 0)
{
	OwningPointer<TextureAttribute> texturehandler;
	texturehandler = i_texture;
	textures[ith_item] = texturehandler;
}