#pragma once

#include "Define.h"
#include "Attribute.h"

namespace Tempest
{

	class TextureAttribute : public Attribute
	{
	public:
		TextureAttribute() : width(), height(), hdrpixels(nullptr)
		{
		}
		~TextureAttribute()
		{
			if (hdrpixels) delete hdrpixels;
		}

		std::vector<Vec3u8t> pixels;
		int width, height;
		TextureType type = static_cast<TextureType>(0);

		// Texture for hdr
		float* hdrpixels;

		virtual bool Load(char const* i_filename, TextureType i_type);
	};

	inline bool TextureAttribute::Load(char const* i_filename, TextureType i_type)
	{
		type = i_type;

		File file(i_filename, File::Format::Default);		

		if (file.GetExtensionName() != ".ttd")
		{
			return Tempest::LoadTexture(i_filename, pixels, width, height, hdrpixels);
		}
		else
		{
			return Resource::Texture::Load(i_filename, width, height, pixels);
		}
	}

}