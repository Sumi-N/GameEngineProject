#pragma once
#include <EntitySystem/Entity.h>
#include <Core/Math/Vector.h>

namespace Tempest 
{
	namespace EntityInfo
	{

		enum ComponentFlags
		{
			None = 0,
			Mesh = 1 << 1,
			Effect = 1 << 2,
			Animation = 1 << 3,
		};

		size_t GetTotalObjectSize();
		Object GetObjectByIndex(int);
		String GetObjectNameByIndex(int);		

		ComponentFlags GetAttachedComponentsByIndex(int);		
	}
}