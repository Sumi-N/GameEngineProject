#pragma once

#include <Logging/Assert.h>
#include <External/tinyobjloader/tiny_obj_loader.h>

#include "GeometryConverter.h"

class OBJConverter :public GeometryConverter
{
public:
	OBJConverter();
	~OBJConverter();

	virtual bool ReadGeometry(std::filesystem::path const) override;
};

