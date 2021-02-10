#pragma once
#include "Define.h"
#include "ResourceData.h"
#include "ResourceLoader.h"

class MeshLoader : ResourceLoader
{
public:
	bool Load(const char*, std::vector<MeshData>&, std::vector<int>&);
};

