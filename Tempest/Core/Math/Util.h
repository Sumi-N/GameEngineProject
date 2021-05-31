#pragma once

#include <math.h>

namespace Math
{
	static float DegreeToRadian(float i_degree)
	{
		return i_degree * 3.14159265359 / 180.0;
	}

	static float RadianToDegree(float i_radian)
	{
		return i_radian * 180 / 3.14159265359;
	}
}