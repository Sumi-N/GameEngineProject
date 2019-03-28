#pragma once
#include "DebugLog.h"
#include "Physics3D.h"

namespace Engine {
	class CollisionDetection
	{
	public:
		CollisionDetection();
		~CollisionDetection();
		static void For2D(Physics3D *, Physics3D *);
	};
}

