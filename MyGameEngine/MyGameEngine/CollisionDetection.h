#pragma once
#include "DebugLog.h"
#include "Physics3D.h"

namespace Engine {
	class CollisionDetection
	{
	public:
		static void Update(float, Physics3D *, Physics3D *);
		static void For2D(Physics3D *, Physics3D *);
		static void UpdateBoundary(Physics3D *);
		static Boundary TranslateToLocal(Physics3D *, Physics3D *);
		static bool CastToXAxis(Physics3D *, Boundary);
		static bool CastToYAxis(Physics3D *, Boundary);
	};
}

