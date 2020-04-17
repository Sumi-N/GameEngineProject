#pragma once

#include "Define.h"
#include "Attribute.h"

enum class TextureType : int8_t
{
	SkyBox = -1,
	Ohter =  -1,

	//////////////////////

	Albedo = 0,
	Normal = 1,
	Roughness = 2,
	Metalic   = 3,
	AmbientOcclusion = 4,

	//////////////////////
	PB_Diffuse  = 0,
	PB_Specular = 1,
	PB_Normal =2,
	PB_Displacement = 3,
};

class TextureAttribute : public Attribute
{
public:
	std::vector<Vec3u8t> pixels;
	int width, height;
	TextureType type = static_cast<TextureType>(0);

	virtual bool Load(char const* i_filename, TextureType i_type);

	// Texture for hdr
	float* hdrpixels;
};

inline bool TextureAttribute::Load(char const* i_filename, TextureType i_type)
{
	type = i_type;

	pixels.clear();
	width = 0;
	height = 0;
	char const* name = i_filename ? i_filename : "";
	if (name[0] == '\0') return false;

	int len = (int)strlen(name);
	if (len < 3) return false;

	bool success = false;

	char ext[3] = { (char)tolower(name[len - 3]), (char)tolower(name[len - 2]), (char)tolower(name[len - 1]) };

	if (strncmp(ext, "png", 3) == 0)
	{
		std::vector<unsigned char> d;
		unsigned int w, h;
		unsigned int error = lodepng::decode(d, w, h, name, LCT_RGB);
		if (error == 0)
		{
			width = w;
			height = h;
			pixels.resize(width * height);
			memcpy(pixels.data(), d.data(), width * height * 3);
		}
		success = (error == 0);
	}
	else if (strncmp(ext, "hdr", 3) == 0)
	{
		int nrComponents;
		stbi_set_flip_vertically_on_load(true);
		hdrpixels = stbi_loadf(i_filename, &width, &height, &nrComponents, 0);

		if (hdrpixels)
		{
			success = true;
		}
	}

	if (success)
	{
		DEBUG_PRINT("Succeed to load texture %s", i_filename);
	}
	else
	{
		DEBUG_PRINT("Failed to load texture %s", i_filename);
		DEBUG_ASSERT(false);
	}

	return success;
}