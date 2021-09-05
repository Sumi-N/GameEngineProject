#pragma once

#include <Utility/File.h>
#include <ResourceManagement/ResourceData.h>

#include <External/cyCodeBase/cyTriMesh.h>

enum class ExtensionType : uint8_t
{
	OBJ,
	FBX,
};

using namespace Resource;

class GeometryConverter
{
public:
	static Tempest::Result ConvertMesh(const char*, const char*);
	static Tempest::Result ConvertSkeletonAndSkeletonMesh(const char*, const char*, const char*);
	static Tempest::Result ConvertAnimationClip(const char*, const char*);

private:
	static Tempest::Result ReadMesh(ExtensionType, const char*, Array<MeshPoint>&, Array<int>&);	
	static Tempest::Result ReadSkeletonMesh(ExtensionType, const char*, Skeleton&, Array<SkeletonMeshPoint>&, Array<int>&);
	static Tempest::Result ReadAnimationClip(ExtensionType, const char*, AnimationClip&);
	static Tempest::Result MatchBoneStructure(const Skeleton&, AnimationClip&);
};

