#pragma once
#include "DebugLog.h"
#include "Physics3D.h"

namespace Engine {
	class CollisionDetection
	{
		enum Axis {X, Y, Z};

	public:
		static void Update(const float, Physics3D *, Physics3D *);
		static void For2D(const float, Physics3D *, Physics3D *);
		static Boundary TranslateToLocal(Physics3D *, Physics3D *);
		static void CordinationTranslation(const float, Physics3D *, Physics3D *, Boundary &, Boundary &);
		static void CastToAxis(Axis, Physics3D *, Physics3D *, Vector2D<float,float> &, Vector2D<float,float> &);
		static bool CastToXAxis(Physics3D *, Boundary);
		static bool CastToYAxis(Physics3D *, Boundary);
		static bool CompareMinMax(const float dt,Vector2D<float,float>, Vector2D<float,float>, Vector2D<float, float>, Vector2D<float, float>);
		static void Collide(Physics3D *, Physics3D *);
	};
}