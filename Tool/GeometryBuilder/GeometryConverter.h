#pragma once

#include <Utility/File.h>
#include <ResourceManagement/ResourceData.h>

#include <External/cyCodeBase/cyTriMesh.h>

class GeometryConverter
{
public:
	static Tempest::Result ConvertGeometry(const char*, const char*);

private:
	static Tempest::Result ReadOBJ(const char*, Array<Resource::MeshPoint>&, Array<int>&);
	static Tempest::Result ReadFBX(const char*, Array<Resource::MeshPoint>&, Array<int>&);
};

