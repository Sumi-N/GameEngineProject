#pragma once

#include "Define.h"
#include "Attribute.h"

namespace Tempest
{
	class TextureAttribute : public Attribute
	{
	public:
		TextureAttribute() : type(TextureType::Default) {}		

		Owner<Resource::Texture> texture;
		TextureType type;

		Result Load(char const* i_filename, TextureType i_type);

	private:
		bool IsLoaded();
	};	

	inline Result TextureAttribute::Load(char const* i_filename, TextureType i_type)
	{
		type = i_type;
		texture = Owner<Resource::Texture>::Create(texture);

		Result result = Resource::Texture::Load(i_filename, *texture);

		if (result)
		{
			DEBUG_PRINT("Succeed loading texture %s", i_filename);			
		}
		else
		{
			DEBUG_PRINT("Failed loading texture %s", i_filename);			
		}

		return result;
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