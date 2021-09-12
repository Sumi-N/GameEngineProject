#pragma once

#include "Define.h"
#include "Attribute.h"

namespace Tempest
{

	class TextureAttribute : public Attribute
	{
	public:
		TextureAttribute() : type(TextureType::Default) {}
		~TextureAttribute() {};
		

		OwningPointer<Resource::Texture> texture;
		TextureType type;

		bool Load(char const* i_filename, TextureType i_type);
		bool IsLoaded();
	};

	inline bool TextureAttribute::Load(char const* i_filename, TextureType i_type)
	{
		type = i_type;
		texture = OwningPointer<Resource::Texture>::Create(texture);
		return Resource::Texture::Load(i_filename, *texture);
	}

	inline bool TextureAttribute::IsLoaded()
	{
		if (texture)
		{
			if (!texture->pixels.Empty())
			{
				return true;
			}
		}

		return false;
	}

}