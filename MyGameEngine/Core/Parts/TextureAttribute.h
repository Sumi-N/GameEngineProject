#pragma once

#include "Define.h"
#include "Attribute.h"


enum class TextureType : int8_t
{
	SkyBox = -1,
	Ohter  = -1,

	//////////////////////

	Albedo           = 0,
	Normal           = 1,
	Roughness        = 2,
	Metalic          = 3,
	AmbientOcclusion = 4,

	//////////////////////

	PB_Diffuse        = 0,
	PB_Specular       = 1,
	PB_Normal         = 2,
	PB_Displacement   = 3,
};

class TextureAttribute : public Attribute
{
public:
	TextureAttribute() : width(), height(), hdrpixels(nullptr) {}
	~TextureAttribute() {if(hdrpixels) delete hdrpixels;}

	std::vector<Vec3u8t> pixels;
	int width, height;
	TextureType type = static_cast<TextureType>(0);

	virtual bool Load(char const* i_filename, TextureType i_type);

	// Texture for hdr
	float* hdrpixels;
};