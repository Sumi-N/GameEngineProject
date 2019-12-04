#pragma once

#include <math.h>
#include <intrin.h>
#include <xmmintrin.h>

namespace Math {

	template <typename T> class Vec2;
	template <typename T> class Vec3;
	template <typename T> class Vec4;

	template <typename T>
	class Vec3
	{
	public:
		union
		{
			struct { T x, y, z;};
			struct { T r, g, b;};
		};

		Vec3() = default;
		Vec3(T i_x, T i_y, T i_z) : x(i_x), y(i_y), z(i_z) {}

		template <typename U> explicit Vec3(Vec3<U> const& u) : x(static_cast<T>(u.x)), y(static_cast<T>(u.y)), z(static_cast<T>(u.z)) {}

		//!@ Operator with constant value
		friend Vec3 operator + (T t, Vec3 const& u) { Vec3 o_v; o_v.x = t + u.x; o_v.y = t + u.y; o_v.z = t + u.z; return o_v; }
		friend Vec3 operator - (T t, Vec3 const& u) { Vec3 o_v; o_v.x = t - u.x; o_v.y = t - u.y; o_v.z = t - u.z; return o_v; }
		friend Vec3 operator * (T t, Vec3 const& u) { Vec3 o_v; o_v.x = t * u.x; o_v.y = t * u.y; o_v.z = t * u.z; return o_v; }
		       Vec3 operator / (T const t)  const { Vec3 o_v; o_v.x = x / t; o_v.y = y / t; o_v.z = z / t; return o_v; }

		//!@ Binary operators
		Vec3 operator + (Vec3 const& i_v) const { Vec3 o_v; o_v.x = x + i_v.x; o_v.y = y + i_v.y; o_v.z = z + i_v.z; return o_v; }
		Vec3 operator - (Vec3 const& i_v) const { Vec3 o_v; o_v.x = x - i_v.x; o_v.y = y - i_v.y; o_v.z = z - i_v.z; return o_v; }
		Vec3 operator * (Vec3 const& i_v) const { Vec3 o_v; o_v.x = x * i_v.x; o_v.y = y * i_v.y; o_v.z = z * i_v.z; return o_v; }
		Vec3 operator / (Vec3 const& i_v) const { Vec3 o_v; o_v.x = x / i_v.x; o_v.y = y / i_v.y; o_v.z = z / i_v.z; return o_v; }

		//!@ Assignment operators
		Vec3 const& operator += (Vec3 const& i_v) { x += i_v.x; y += i_v.y; z += i_v.z; return *this; }
		Vec3 const& operator -= (Vec3 const& i_v) { x -= i_v.x; y -= i_v.y; z -= i_v.z; return *this; }
		Vec3 const& operator *= (Vec3 const& i_v) { x *= i_v.x; y *= i_v.y; z *= i_v.z; return *this; }
		Vec3 const& operator /= (Vec3 const& i_v) { x /= i_v.x; y /= i_v.y; z /= i_v.z; return *this; }
		Vec3 const& operator += (T    const  t) { x += t; y += t; z += t; return *this; }
		Vec3 const& operator -= (T    const  t) { x -= t; y -= t; z -= t; return *this; }
		Vec3 const& operator *= (T    const  t) { x *= t; y *= t; z *= t; return *this; }
		Vec3 const& operator /= (T    const  t) { x /= t; y /= t; z /= t; return *this; }

		bool operator == (Vec3 const& i_v) const { return x == i_v.x && y == i_v.y && z == i_v.z; }
		bool operator != (Vec3 const& i_v) const { return x != i_v.x && y != i_v.y && z != i_v.z; }

		void Zero      ()       { x = 0; y = 0; z = 0; }
		bool IsZero    () const { return x == static_cast<T>(0) && y == static_cast<T>(0) && z == static_cast<T>(0); }
		void Normalize ()       { *this /= Length(); }
		T    Length    () const { return sqrt(static_cast<T>(x)* static_cast<T>(x) + static_cast<T>(y)* static_cast<T>(y) + static_cast<T>(z)* static_cast<T>(z)); }
	};

	template <>
	class Vec3<float>
	{
	public:
		union 
		{
			__m128 m_vec;
			struct { float x, y, z; };
			struct { float r, g, b; };
		};

		Vec3<float> operator + (Vec3<float> const& i_v) const { Vec3<float> o_v; o_v.m_vec = _mm_add_ps(m_vec, i_v.m_vec); return o_v;}
	};

} // <- namespace Math


//typedef Math::Vec3<unsigned short>   Vec3us;
//typedef Math::Vec3<short>            Vec3s;
//typedef Math::Vec3<unsigned int>     Vec3ui;
//typedef Math::Vec3<int>              Vec3i;
typedef Math::Vec3<float>            Vec3f;
typedef Math::Vec3<double>           Vec3d;