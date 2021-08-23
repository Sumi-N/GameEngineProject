#pragma once

#include <Utility/File.h>
#include <ResourceManagement/ResourceData.h>

#include <External/cyCodeBase/cyTriMesh.h>

enum class ConversionType : uint8_t
{
	Mesh,
	SkeletonMesh,
};

enum class ExtensionType : uint8_t
{
	OBJ,
	FBX,
};

class GeometryConverter
{
public:
	static Tempest::Result ConvertGeometry(ConversionType, const char*, const char*);

private:
	static Tempest::Result ReadMesh(ExtensionType, const char*, Array<Resource::MeshPoint>&, Array<int>&);	
	static Tempest::Result ReadSkeletonMesh(ExtensionType, const char*, Array<Resource::SkeletonMeshPoint>&, Array<int>&);
};

