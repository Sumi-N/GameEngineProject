#pragma once
#include <fbxsdk.h>

#include <ResourceManagement/ResourceData.h>


namespace FBXLoader
{
	/////////////////////////////////////
	// public method
	/////////////////////////////////////

	bool Init(const char*);
	bool LoadMesh(Array<Resource::MeshPoint>&, Array<int>&);
	bool LoadSkeletonMesh(Array<Resource::SkeletonMeshPoint>&, Array<int>&);
	bool LoadSkeleton(Resource::Skeleton&);
	void PrintData();
	bool CleanUp();

	/////////////////////////////////////
	// private method
	/////////////////////////////////////

	void PrintNode(FbxNode*);
	void PrintTabs();
	void PrintAttribute(FbxNodeAttribute*);
	FbxString GetAttributeTypeName(FbxNodeAttribute::EType);
	FbxAMatrix GetGeometryTransformation(FbxNode* inNode);

	void ProcessSkeletonHierarchyRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex, Resource::Skeleton& skeleton);
}

