#include <fstream>
#include <iostream>

#include <Utility/File.h>
#include "TextureConverter.h"

#include <External/loadpng/lodepng.h>

//#ifndef STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
//#endif
//#include <External/stb/stb_image.h>

Tempest::Result TextureConverter::ConvertTexture(const char* i_filename, const char* o_filename)
{
	Tempest::File in(i_filename, Tempest::File::Format::BinaryRead);
	Tempest::File out(o_filename, Tempest::File::Format::BinaryWrite);

	if (in.GetExtensionName() == ".png")
	{
		Tempest::Array<unsigned char> d;
		unsigned int w, h;
		unsigned int error = lodepng::decode(d, w, h, i_filename, LCT_RGB);

		if (error == 0)
		{	
			out.Open();
			out.Write((void*)&w, sizeof(int));
			out.Write((void*)&h, sizeof(int));
			out.Write((void*)d.data(), sizeof(unsigned char) * w * h * static_cast<size_t>(3));
			out.Close();

			return Tempest::ResultValue::Success;
		}		
	}

	return Tempest::ResultValue::Failure;
}

