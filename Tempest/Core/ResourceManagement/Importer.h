#pragma once

#include "Define.h"
#include "ResourceData.h"

namespace Tempest
{
	void ReadGeometry(const char*, std::vector<MeshData>&, std::vector<int>&);
	bool LoadTexture(const char*, std::vector<Vec3u8t>&, int&, int&, float*&);
}