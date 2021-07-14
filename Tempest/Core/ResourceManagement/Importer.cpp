#include "Importer.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <External/stb/stb_image.h>


bool Tempest::LoadTexture(const char* i_filename, std::vector<Vec3u8t>& pixels, int& width, int& height, float*& hdrpixels)
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
			pixels.resize(static_cast<size_t>(width)* static_cast<size_t>(height));
			memcpy(pixels.data(), d.data(), static_cast<size_t>(width)* static_cast<size_t>(height)* static_cast<size_t>(3));
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
		DEBUG_PRINT("Succeed loading texture %s", i_filename);
	}
	else
	{
		DEBUG_PRINT("Failed loading texture %s", i_filename);
		DEBUG_ASSERT(false);
	}

	return success;
}