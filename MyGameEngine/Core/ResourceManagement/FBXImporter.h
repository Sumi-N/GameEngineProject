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
	void ImportMesh(FbxNode* pNode, std::vector<MeshData>& data, std::vector<int>& index);
};

