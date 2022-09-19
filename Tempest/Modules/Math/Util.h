#pragma once

#include <math.h>

namespace Math
{
	constexpr float pi = 3.14159265359f;

	static float DegreeToRadian(float i_degree)
	{
		return i_degree * pi / 180.0f;
	}

	static float RadianToDegree(float i_radian)
	{
		return i_radian * 180.0f / pi;
	}

	static bool EpsilonEqual(float const& x, float const& y, float const& epsilon)
	{
		return abs(x - y) < epsilon;
	}

	static bool EpsilonNotEqual(float const& x, float const& y, float const& epsilon)
	{
		return abs(x - y) >= epsilon;
	}
}