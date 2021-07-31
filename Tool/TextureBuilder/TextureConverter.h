#pragma once

#include <Math/Vector.h>
#include <Utility/File.h>
#include <ResourceManagement/ResourceData.h>

#include <External/loadpng/lodepng.h>

class TextureConverter
{
public:
	static Tempest::Result ConvertTexture(const char*, const char*);
};

