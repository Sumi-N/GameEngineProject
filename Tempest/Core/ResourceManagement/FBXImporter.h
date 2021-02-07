#pragma once

#include "Define.h"
#include "ResourceData.h"

class FBXImporter
{
public:

	bool Import(const char*);

	void PrintNode(FbxNode* pNode);
	void ImportNode(FbxNode* pNode);
	void PrintAttribute(FbxNodeAttribute* pAttribute);
	FbxString GetAttributeTypeName(FbxNodeAttribute::EType type);
	void PrintTabs();

public:
	bool LoadMesh(const char* filename, std::vector<MeshData>& data, std::vector<int>& index);
	bool ImportMesh(FbxNode* pNode, std::vector<MeshData>& data, std::vector<int>& index, Mat4f model_matrix);

	bool ImportMaterial(FbxSurfaceMaterial*, MaterialData&);

	void ProcessSkeletonHierarchy(FbxNode*, Skeleton);
	void ProcessSkeletonHierarchyRecursively(FbxNode* , int, int, int, Skeleton);

	void ProcessJointsAndAnimations(FbxNode*, Skeleton);
	FbxAMatrix GetGeometryTransformation(FbxNode*);

	int FindJointIndexUsingName(const char*, Skeleton);
	Mat4f convertFBXMatrix(FbxAMatrix);
};

