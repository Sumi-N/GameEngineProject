#pragma once

#include <Logging/Assert.h>
#include <External/tinyobjloader/tiny_obj_loader.h>

#include "Importer.h"

class OBJImporter :public Importer
{
public:
	OBJImporter();
	~OBJImporter();

	virtual bool LoadMesh(std::string) override;
};

