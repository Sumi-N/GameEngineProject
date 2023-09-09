#pragma once
#include <EntitySystem/Entity.h>
#include <Modules/Math/Vector.h>

namespace Tempest
{
	namespace EntityInfo
	{
		enum ComponentFlags
		{
			None = 0,
			ObjectFlag = 1 << 1,
			CameraFlag = 1 << 2,
			LightFlag = 1 << 3,
			MeshFlag = 1 << 4,
			EffectFlag = 1 << 5,
			AnimationFlag = 1 << 6,
		};

		size_t GetTotalObjectSize();
		Object GetObjectByIndex(int);
		String GetObjectNameByIndex(int);

		ComponentFlags GetAttachedComponentsInfoByIndex(int);
	}
}