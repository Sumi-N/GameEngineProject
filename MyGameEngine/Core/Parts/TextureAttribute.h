#pragma once

#include "Define.h"
#include "Attribute.h"

class TextureAttribute : public Attribute
{
public:
	std::vector<Vec3u8t> pixels;
	int width, height;

	bool Load(char const* i_filename);
};

inline bool TextureAttribute::Load(char const* i_filename)
{
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

	if (success)
	{
		DEBUG_PRINT("Succeed to load texture %s", i_filename);
	}
	else
	{
		DEBUG_ASSERT(false);
		DEBUG_PRINT("Failed to load texture %s", i_filename);
	}

	return success;
}