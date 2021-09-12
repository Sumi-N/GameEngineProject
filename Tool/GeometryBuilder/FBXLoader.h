#pragma once
#include <fbxsdk.h>

#include <ResourceManagement/ResourceData.h>

using namespace Resource;

namespace FBXLoader
{
	/////////////////////////////////////
	// public method
	/////////////////////////////////////

	bool Init(const char*);
	bool LoadMesh(Array<MeshPoint>&, Array<int>&);
	bool LoadSkeletonMesh(Array<SkeletonMeshPoint>&, Array<int>&, const std::map<String, int>&);
	bool LoadSkeleton(Skeleton&, std::map<String, int>&);
	bool LoadAnimationClip(AnimationClip&);
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

	void ProcessSkeletonHierarchyRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex, Resource::Skeleton& skeleton, std::map<String, int>& joint_map);		
	void ProcessAnimationSampleRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex, AnimationSample& sample, FbxTime time);

	int FindJointIndexUsingName(std::string name, const std::map<String, int>& joint_map);
}

