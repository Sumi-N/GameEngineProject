#pragma once

#include "Define.h"
#include "Component.h"
#include "TextureAttribute.h"
#include "MaterialAttribute.h"

namespace Tempest
{

	class EffectComponent : public Component
	{
	public:
		EffectComponent();
		~EffectComponent() override;

		void RegisterShaderPath(const char**);
		void SetMaterial(MaterialAttribute*);
		void SetMaterial(OwningPointer<MaterialAttribute>);
		void SetTexture(TextureAttribute*);
		void SetTexture(OwningPointer<TextureAttribute>);
		void ReplaceTexture(TextureAttribute*, int);
		
		const char* shaderpaths[5];
		Array<OwningPointer<TextureAttribute>> texture_attributes;
		OwningPointer<MaterialAttribute> material_attribute;
	};

	inline EffectComponent::EffectComponent() : shaderpaths()
	{
	}

	inline EffectComponent::~EffectComponent()
	{

	}

	inline void EffectComponent::RegisterShaderPath(const char** shaderpaths)
	{
		this->shaderpaths[0] = shaderpaths[0];
		this->shaderpaths[1] = shaderpaths[1];
		this->shaderpaths[2] = shaderpaths[2];
		this->shaderpaths[3] = shaderpaths[3];
		this->shaderpaths[4] = shaderpaths[4];
	}

	inline void EffectComponent::SetMaterial(MaterialAttribute* i_material)
	{
		material_attribute = i_material;
	}

	inline void EffectComponent::SetMaterial(OwningPointer<MaterialAttribute> i_material)
	{
		material_attribute = i_material;
	}

	inline void EffectComponent::SetTexture(TextureAttribute* i_texture)
	{
		OwningPointer<TextureAttribute> texturehandler;
		texturehandler = i_texture;
		texture_attributes.PushBack(texturehandler);
	}

	inline void EffectComponent::SetTexture(OwningPointer<TextureAttribute> i_texture)
	{
		texture_attributes.PushBack(i_texture);
	}

	inline void EffectComponent::ReplaceTexture(TextureAttribute* i_texture, int ith_item = 0)
	{
		OwningPointer<TextureAttribute> texturehandler;
		texturehandler = i_texture;
		texture_attributes[ith_item] = texturehandler;
	}

}