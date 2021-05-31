#pragma once
#include "Define.h"
#include "ResourceData.h"
#include <Logging/Result.h>

namespace Tempest
{

	class ResourceLoader
	{

	};

	class MeshLoader : ResourceLoader
	{
	public:
		Result Load(const char*, std::vector<Resource::Mesh>&, std::vector<int>&);
	};

}

