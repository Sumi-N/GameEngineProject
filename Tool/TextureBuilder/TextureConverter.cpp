#include "TextureConverter.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <External/stb/stb_image.h>
#include <External/loadpng/lodepng.h>

Tempest::Result TextureConverter::ConvertTexture(const char* i_filename, const char* o_filename)
{
	Tempest::File in(i_filename, Tempest::File::Format::BinaryRead);
	Tempest::File out(o_filename, Tempest::File::Format::BinaryWrite);

	if (in.GetExtensionName() == ".png")
	{
		Tempest::Array<unsigned char> pixels;
		unsigned int width, height;
		unsigned int error = lodepng::decode(pixels, width, height, i_filename, LCT_RGB);
		// This needs to be changed based on the texture type
		TextureType type = TextureType::Albedo;

		if(error != 0)
		{
			return Tempest::ResultValue::Failure;
		}

		RETURN_IFNOT_SUCCESS(out.Open());
		RETURN_IFNOT_SUCCESS(out.Write((void*)&type, sizeof(TextureType)));
		RETURN_IFNOT_SUCCESS(out.Write((void*)&width, sizeof(int)));
		RETURN_IFNOT_SUCCESS(out.Write((void*)&height, sizeof(int)));
		RETURN_IFNOT_SUCCESS(out.Write((void*)pixels.data(), sizeof(unsigned char) * width * height * static_cast<size_t>(3)));

		out.Close();

		return Tempest::ResultValue::Success;
	}
	else if (in.GetExtensionName() == ".hdr")
	{
		float* pixels = nullptr;
		int nrComponents;
		int width, height;
		TextureType type = TextureType::SkyBox;

		stbi_set_flip_vertically_on_load(true);

		pixels = stbi_loadf(i_filename, &width, &height, &nrComponents, 0);

		if (!pixels)
		{
			return Tempest::ResultValue::Failure;
		}

		RETURN_IFNOT_SUCCESS(out.Open());
		RETURN_IFNOT_SUCCESS(out.Write((void*)&type, sizeof(TextureType)));	
		RETURN_IFNOT_SUCCESS(out.Write((void*)&width, sizeof(int)));
		RETURN_IFNOT_SUCCESS(out.Write((void*)&height, sizeof(int)));
		RETURN_IFNOT_SUCCESS(out.Write((void*)pixels, sizeof(float) * width * height * static_cast<size_t>(3)));

		out.Close();

		delete pixels;

		return Tempest::ResultValue::Success;
	}

	return Tempest::ResultValue::Failure;
}

