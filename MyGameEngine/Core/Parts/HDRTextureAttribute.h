#pragma once

#include "Define.h"
#include "TextureAttribute.h"

class HDRTextureAttribute : public TextureAttribute
{
public:
	std::vector<float> data;

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
	float * data = stbi_loadf("newport_loft.hdr", &width, &height, &nrComponents, 0);

	if (data)
	{
		for (int i = 0; i < width * height; i++)
		{
			this->data.push_back(data[i]);
		}
	}
	else
	{
		DEBUG_ASSERT(false);
	}

	stbi_image_free(data);
}