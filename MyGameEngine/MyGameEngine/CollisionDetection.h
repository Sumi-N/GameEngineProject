#pragma once
#include "DebugLog.h"
#include "Physics3D.h"

// For Collision Detection
struct Boundary
{
	Vector3D ur; // Upper right
	Vector3D ul; // Upper left
	Vector3D lr; // Lower right
	Vector3D ll; // Lower left
};

namespace Engine {
	class CollisionDetection
	{
		enum Axis {X, Y, Z};

	public:
		static void Update(const float, Physics3D *, Physics3D *);

		static void Collision2D(const float, const float, Physics3D *, Physics3D *);

		static void UpdateBoundary(const float, const float, Physics3D *, Boundary &, Boundary &);
		static void CordinationTranslation(const float, const float, Physics3D *, Boundary &, Boundary &);
		static void CastToAxis(Axis, Boundary &, Boundary &, Vector2D<float, float> &, Vector2D<float, float> &);
		static void GetMinMax(Vector2D<float,float> &, float, float, float, float);
		static bool CheckOverlapping(Vector2D<float,float>,Vector2D<float,float>, Vector2D<float,float>);
		static float CalculateCollisionTiming(const float,Vector2D<float,float>, Vector2D<float, float>, Vector2D<float, float>);
		static void Collide(Physics3D *, Physics3D *);

		///////////Legacy///////////
		//static void For2D(const float, Physics3D *, Physics3D *);
		//static Boundary TranslateToLocal(Physics3D *, Physics3D *);
		//static bool CastToXAxis(Physics3D *, Boundary);
		//static bool CastToYAxis(Physics3D *, Boundary);
	};
}