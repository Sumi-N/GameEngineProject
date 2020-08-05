#pragma once

#include "Define.h"

namespace Debug
{
	class Ray
	{
	public:
		Ray() : startpoint(Vec3f()), endpoint(Vec3f()), direction(Vec3f(0, 0, -1.0f)), length(100){ }

		Vec3f startpoint;
		Vec3f endpoint;
		Vec3f direction;
		float length;

		void GetEndPoint()
		{
			direction.Normalize();
			endpoint = startpoint + length * direction;
		}
		
	};
}
