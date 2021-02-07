#pragma once
#include <Configuration/Configuration.h>

#include <Logging/Assert.h>

#include <cmath>
#include <math.h>
#include <intrin.h>
#include <xmmintrin.h>

#define _USE_MATH_DEFINES

namespace Math
{
	template <typename T> inline T     Sqrt(T const &i)           { return (T)std::sqrt(i); }
	template <typename T> inline T Pi () { return static_cast<T>(3.141592653589793238462643383279502884197169); }


#ifdef _USEINTRINSIC_
	template <>           inline float Sqrt<float>(float const&i) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ps1(i))); }
#endif // _USEINTRINSIC_	
}
