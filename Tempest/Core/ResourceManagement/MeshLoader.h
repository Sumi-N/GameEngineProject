#pragma once
#include "Define.h"
#include "ResourceData.h"
#include "ResourceLoader.h"
#include <Logging/Result.h>

namespace Tempest
{

	class MeshLoader : ResourceLoader
	{
	public:
		Result Load(const char*, std::vector<MeshData>&, std::vector<int>&);
	};

}

