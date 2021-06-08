#pragma once
#include <fbxsdk.h>

#include <ResourceManagement/ResourceData.h>


namespace FBXLoader
{
	bool Init(const char*);
	void PrintData();
	void PrintNode(FbxNode*);
	bool CleanUp();

	void PrintTabs();
	void PrintAttribute(FbxNodeAttribute*);
	FbxString GetAttributeTypeName(FbxNodeAttribute::EType);

	bool LoadMesh(std::vector<Resource::MeshPoint>& , std::vector<int>&);
	FbxAMatrix GetGeometryTransformation(FbxNode* inNode);
}

