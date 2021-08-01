#pragma once

#include "Define.h"
#include "Attribute.h"

namespace Tempest
{

	class TextureAttribute : public Attribute
	{
	public:
		TextureAttribute() : width(0), height(0) {}
		~TextureAttribute() = default;
		

		Array<Vec3u8t> pixels;
		size_t width, height;
		TextureType type = static_cast<TextureType>(0);

		virtual bool Load(char const* i_filename, TextureType i_type);
	};

	inline bool TextureAttribute::Load(char const* i_filename, TextureType i_type)
	{
		type = i_type;				
		return Resource::Texture::Load(i_filename, width, height, pixels);		
	}

}