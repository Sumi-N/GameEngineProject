#pragma once
#include <EntitySystem/Entity.h>
#include <Core/Math/Vector.h>

namespace Tempest 
{	
	namespace EntityInfo 
	{
		enum ComponentFlags
		{
			None      = 0,
			Mesh      = 1 << 1,
			Effect    = 1 << 2,
			Animation = 1 << 3,
		};

		//enum AttributeFlags
		//{
		//	None = 0,
		//	Material = 1 << 0,
		//	Texture = 2 << 0,
		//};

		size_t GetTotalObjectSize();
		String GetObjectNameByIndex(int);
		Vec3f GetObjectPositionByIndex(int);
		Vec3f GetObjectRotationByIndex(int);
		Vec3f GetObjectScaleByIndex(int);

		ComponentFlags GetAttachedComponentsByIndex(int);
	}
}

