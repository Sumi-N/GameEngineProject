#pragma once

#include <Math/Vector.h>
#include <Utility/Result.h>
#include <ResourceManagement/ResourceData.h>

class TextureConverter
{
public:
	static Tempest::Result ConvertTexture(const char*, const char*);
};

