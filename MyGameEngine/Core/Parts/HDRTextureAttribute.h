#pragma once

#include "Define.h"
#include "TextureAttribute.h"

class HDRTextureAttribute : public TextureAttribute
{
public:
	std::vector<float> data;
	float* data2;

	bool Load(char const*, TextureType ) override;
};

inline bool HDRTextureAttribute::Load(char const* i_filename, TextureType i_type)
{
	if (i_type != TextureType::SkyBox)
	{
		DEBUG_ASSERT(false);
	}

	type = TextureType::SkyBox;

	int nrComponents;
	stbi_set_flip_vertically_on_load(true);
	data2 = stbi_loadf(i_filename, &width, &height, &nrComponents, 0);

	if (data2)
	{
		for (int i = 0; i < width * height; i++)
		{
			//this->data.push_back(data[i]);
		}
	}
	else
	{
		DEBUG_ASSERT(false);
	}

	//stbi_image_free(data);
	return true;
}