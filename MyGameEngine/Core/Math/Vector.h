#pragma once

#include "Define.h"

#include <math.h>
#include <intrin.h>
#include <xmmintrin.h>

namespace Math {

	template <typename T> class Vec2;
	template <typename T> class Vec3;
	template <typename T> class Vec4;

	template <typename T>
	class Vec2
	{
	public:
		union
		{
			struct { T x, y;};
			T ele[2];
		};

		//!@ Constructor
		Vec2() = default;
		Vec2(T i_x, T i_y) : x(i_x), y(i_y) {}

		template <typename U> 
		explicit Vec2(Vec2<U> const& u) : x(static_cast<T>(u.x)), y(static_cast<T>(u.y)) {}
		explicit Vec2(Vec3<T> const& t) : x(t.x), y(t.y) {}

		//!@ Operator with constant value
		friend Vec2 operator + (T t, Vec2 const& u) { Vec2 o_v; o_v.x = t + u.x; o_v.y = t + u.y; return o_v; }
		friend Vec2 operator - (T t, Vec2 const& u) { Vec2 o_v; o_v.x = t - u.x; o_v.y = t - u.y; return o_v; }
		friend Vec2 operator * (T t, Vec2 const& u) { Vec2 o_v; o_v.x = t * u.x; o_v.y = t * u.y; return o_v; }
		       Vec2 operator / (T const t)  const { Vec2 o_v; o_v.x = x / t; o_v.y = y / t; return o_v; }

		//!@ Binary operators
		Vec2 operator + (Vec2 const& i_v) const { Vec2 o_v; o_v.x = x + i_v.x; o_v.y = y + i_v.y; return o_v; }
		Vec2 operator - (Vec2 const& i_v) const { Vec2 o_v; o_v.x = x - i_v.x; o_v.y = y - i_v.y; return o_v; }
		Vec2 operator * (Vec2 const& i_v) const { Vec2 o_v; o_v.x = x * i_v.x; o_v.y = y * i_v.y; return o_v; }
		Vec2 operator / (Vec2 const& i_v) const { Vec2 o_v; o_v.x = x / i_v.x; o_v.y = y / i_v.y; return o_v; }

		//!@ Assignment operators
		Vec2 const& operator += (Vec2 const& i_v) { x += i_v.x; y += i_v.y; return *this; }
		Vec2 const& operator -= (Vec2 const& i_v) { x -= i_v.x; y -= i_v.y; return *this; }
		Vec2 const& operator *= (Vec2 const& i_v) { x *= i_v.x; y *= i_v.y; return *this; }
		Vec2 const& operator /= (Vec2 const& i_v) { x /= i_v.x; y /= i_v.y; return *this; }
		Vec2 const& operator += (T    const  t) { x += t; y += t; return *this; }
		Vec2 const& operator -= (T    const  t) { x -= t; y -= t; return *this; }
		Vec2 const& operator *= (T    const  t) { x *= t; y *= t; return *this; }
		Vec2 const& operator /= (T    const  t) { x /= t; y /= t; return *this; }

		bool operator == (Vec2 const& i_v) const { return x == i_v.x && y == i_v.y; }
		bool operator != (Vec2 const& i_v) const { return x != i_v.x && y != i_v.y; }

		void Set       (T i_x, T i_y) {x = i_x, y = i_y; }
		void Zero      ()       { x = 0; y = 0; }
		bool IsZero    () const { return x == static_cast<T>(0) && y == static_cast<T>(0); }
		void Normalize ()       { *this /= Length(); }
		T    Length    () const { return Sqrt(static_cast<T>(x)* static_cast<T>(x) + static_cast<T>(y)* static_cast<T>(y)); }
		float Dot       (Vec2 i_v)       { return x * i_v.x + y * i_v.y; }

		static float Length   (Vec2 i_v) { return Sqrt(static_cast<T>(i_v.x)* static_cast<T>(i_v.x) + static_cast<T>(i_v.y)* static_cast<T>(i_v.y)); }
		static Vec2 Normalize (Vec2 i_v) { return i_v/Length(i_v); }
	};

	template <typename T>
	class Vec3
	{
	public:
		union
		{
			struct { T x, y, z;};
			struct { T r, g, b;};
			T ele[3];
		};

		//!@ Constructor
		Vec3() = default;
		Vec3(T i_x, T i_y, T i_z) : x(i_x), y(i_y), z(i_z) {}

		template <typename U> 
		explicit Vec3(Vec3<U> const& u) : x(static_cast<T>(u.x)), y(static_cast<T>(u.y)), z(static_cast<T>(u.z)) {}
		explicit Vec3(Vec4<T> const& t) : x(t.x), y(t.y), z(t.z) {}

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

		void Set       (T i_x, T i_y, T i_z) {x = i_x, y = i_y, z = i_z;}
		void Zero      ()       { x = 0; y = 0; z = 0; }
		bool IsZero    () const { return x == static_cast<T>(0) && y == static_cast<T>(0) && z == static_cast<T>(0); }
		void Normalize ()       { *this /= Length(); }
		T    Length    () const { return Sqrt(static_cast<T>(x)* static_cast<T>(x) + static_cast<T>(y)* static_cast<T>(y) + static_cast<T>(z)* static_cast<T>(z)); }
		float Dot       (Vec3 i_v)       { return x * i_v.x + y * i_v.y + z * i_v.z; }
		Vec3  Cross     (Vec3 i_v)       { return Vec3(y * i_v.z - z * i_v.y, z * i_v.x - x * i_v.z, x * i_v.y - y * i_v.x); }

		static float Length   (Vec3 i_v) { return Sqrt(static_cast<T>(i_v.x)* static_cast<T>(i_v.x) + static_cast<T>(i_v.y)* static_cast<T>(i_v.y) + static_cast<T>(i_v.z)* static_cast<T>(i_v.z)); }
		static Vec3 Normalize (Vec3 i_v) { return i_v/Length(i_v); }
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

		//!@ Constructor
		Vec3() = default;
		Vec3(float i_x, float i_y, float i_z) : x(i_x), y(i_y), z(i_z) {}

		template <typename U>
		explicit Vec3(Vec3<U> const& u) : x(static_cast<float>(u.x)), y(static_cast<float>(u.y)), z(static_cast<float>(u.z)){}
		template <typename U>
		explicit Vec3(Vec4<U> const& t) : x(t.x), y(t.y), z(t.z) {}

		//!@ Operator with constant value
		friend Vec3 operator + (float t, Vec3 const& u)	{Vec3 o_v; o_v.x = t + u.x; o_v.y = t + u.y; o_v.z = t + u.z; return o_v;}
		friend Vec3 operator - (float t, Vec3 const& u) {Vec3 o_v; o_v.x = t - u.x; o_v.y = t - u.y; o_v.z = t - u.z; return o_v;}
		friend Vec3 operator * (float t, Vec3 const& u) {Vec3 o_v; o_v.x = t * u.x; o_v.y = t * u.y; o_v.z = t * u.z; return o_v;}
		Vec3 operator / (float const t)  const	{Vec3 o_v; o_v.x = x / t; o_v.y = y / t; o_v.z = z / t; return o_v;	}

		//!@ Binary operators
		Vec3<float> operator + (Vec3<float> const& i_v) const;
		Vec3<float> operator - (Vec3<float> const& i_v) const;
		Vec3<float> operator * (Vec3<float> const& i_v) const;
		Vec3<float> operator / (Vec3<float> const& i_v) const;

		//!@ Assignment operators
		Vec3 const& operator += (Vec3 const& i_v) { x += i_v.x; y += i_v.y; z += i_v.z; return *this; }
		Vec3 const& operator -= (Vec3 const& i_v) { x -= i_v.x; y -= i_v.y; z -= i_v.z; return *this; }
		Vec3 const& operator *= (Vec3 const& i_v) { x *= i_v.x; y *= i_v.y; z *= i_v.z; return *this; }
		Vec3 const& operator /= (Vec3 const& i_v) { x /= i_v.x; y /= i_v.y; z /= i_v.z; return *this; }
		Vec3 const& operator += (float    const  t) { x += t; y += t; z += t; return *this; }
		Vec3 const& operator -= (float    const  t) { x -= t; y -= t; z -= t; return *this; }
		Vec3 const& operator *= (float    const  t) { x *= t; y *= t; z *= t; return *this; }
		Vec3 const& operator /= (float    const  t) { x /= t; y /= t; z /= t; return *this; }

		bool operator == (Vec3 const& i_v) const { return x == i_v.x && y == i_v.y && z == i_v.z; }
		bool operator != (Vec3 const& i_v) const { return x != i_v.x && y != i_v.y && z != i_v.z; }

		void  Set(float i_x, float i_y, float i_z){x = i_x, y = i_y, z = i_z;}
		void  Zero      ()       { x = 0; y = 0; z = 0; }
		bool  IsZero    () const { return x == static_cast<float>(0) && y == static_cast<float>(0) && z == static_cast<float>(0); }
		void  Normalize ()       { *this /= Length(); }
		float Length() const { return Sqrt(static_cast<float>(x)* static_cast<float>(x) + static_cast<float>(y)* static_cast<float>(y) + static_cast<float>(z)* static_cast<float>(z)); }
		float Dot       (Vec3 i_v)       {return x * i_v.x + y * i_v.y + z * i_v.z; }
		Vec3  Cross     (Vec3 i_v)       {return Vec3(y * i_v.z - z * i_v.y, z * i_v.x - x * i_v.z, x * i_v.y - y * i_v.x); }

		static float Length   (Vec3 i_v) { return Sqrt(static_cast<float>(i_v.x)* static_cast<float>(i_v.x) + static_cast<float>(i_v.y)* static_cast<float>(i_v.y) + static_cast<float>(i_v.z)* static_cast<float>(i_v.z)); }
		static Vec3 Normalize (Vec3 i_v) { return i_v/Length(i_v); }
	};

	template <typename T>
	class Vec4
	{
	public:
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			T ele[4];
		};

		//!@ Constructor
		Vec4() = default;
		Vec4(Vec3<T> i_v, T i_w) : x(i_v.x), y(i_v.y), z(i_v.z), w(i_w) {}
		Vec4(T i_x, T i_y, T i_z, T i_w) : x(i_x), y(i_y), z(i_z), w(i_w) {}

		template <typename U> 
		explicit Vec4(Vec4<U> const& u) : x(static_cast<T>(u.x)), y(static_cast<T>(u.y)), z(static_cast<T>(u.z)), z(static_cast<T>(u.w)) {}
		explicit Vec4(Vec3<T> const& t) : x(t.x), y(t.y), z(t.z), w(0) {}

		//!@ Operator with constant value
		friend Vec4 operator + (T t, Vec4 const& u) { Vec4 o_v; o_v.x = t + u.x; o_v.y = t + u.y; o_v.z = t + u.z; o_v.w = t + u.w; return o_v; }
		friend Vec4 operator - (T t, Vec4 const& u) { Vec4 o_v; o_v.x = t - u.x; o_v.y = t - u.y; o_v.z = t - u.z; o_v.w = t - u.w; return o_v; }
		friend Vec4 operator * (T t, Vec4 const& u) { Vec4 o_v; o_v.x = t * u.x; o_v.y = t * u.y; o_v.z = t * u.z; o_v.w = t * u.w; return o_v; }
		Vec4 operator / (T const t)  const { Vec4 o_v; o_v.x = x / t; o_v.y = y / t; o_v.z = z / t; o_v.w = w / t; return o_v; }

		//!@ Binary operators
		Vec4 operator + (Vec4 const& i_v) const { Vec4 o_v; o_v.x = x + i_v.x; o_v.y = y + i_v.y; o_v.z = z + i_v.z; o_v.w = w + i_v.w; return o_v; }
		Vec4 operator - (Vec4 const& i_v) const { Vec4 o_v; o_v.x = x - i_v.x; o_v.y = y - i_v.y; o_v.z = z - i_v.z; o_v.w = w - i_v.w; return o_v; }
		Vec4 operator * (Vec4 const& i_v) const { Vec4 o_v; o_v.x = x * i_v.x; o_v.y = y * i_v.y; o_v.z = z * i_v.z; o_v.w = w * i_v.w; return o_v; }
		Vec4 operator / (Vec4 const& i_v) const { Vec4 o_v; o_v.x = x / i_v.x; o_v.y = y / i_v.y; o_v.z = z / i_v.z; o_v.w = w / i_v.w; return o_v; }

		//!@ Assignment operators
		Vec4 const& operator += (Vec4 const& i_v) { x += i_v.x; y += i_v.y; z += i_v.z; w += i_v.w; return *this; }
		Vec4 const& operator -= (Vec4 const& i_v) { x -= i_v.x; y -= i_v.y; z -= i_v.z; w -= i_v.w; return *this; }
		Vec4 const& operator *= (Vec4 const& i_v) { x *= i_v.x; y *= i_v.y; z *= i_v.z; w *= i_v.w; return *this; }
		Vec4 const& operator /= (Vec4 const& i_v) { x /= i_v.x; y /= i_v.y; z /= i_v.z; w /= i_v.w; return *this; }
		Vec4 const& operator += (T    const  t) { x += t; y += t; z += t; w += t; return *this; }
		Vec4 const& operator -= (T    const  t) { x -= t; y -= t; z -= t; w -= t; return *this; }
		Vec4 const& operator *= (T    const  t) { x *= t; y *= t; z *= t; w *= t; return *this; }
		Vec4 const& operator /= (T    const  t) { x /= t; y /= t; z /= t; w /= t; return *this; }

		bool operator == (Vec4 const& i_v) const { return x == i_v.x && y == i_v.y && z == i_v.z && w == i_v.w; }
		bool operator != (Vec4 const& i_v) const { return x != i_v.x && y != i_v.y && z != i_v.z && w != i_v.w; }

		void Zero() { x = 0; y = 0; z = 0; w = 0; }
		bool IsZero() const { return x == static_cast<T>(0) && y == static_cast<T>(0) && z == static_cast<T>(0) && w == static_cast<T>(0); }
		void Normalize() { *this /= Length(); }
		T    Length() const { return sqrt(static_cast<T>(x)* static_cast<T>(x) + static_cast<T>(y)* static_cast<T>(y) + static_cast<T>(z)* static_cast<T>(z) + static_cast<T>(w)* static_cast<T>(w)); }
	};

	template <>
	class Vec4<float>
	{
	public:
		union
		{
			__m128 m_vec;
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
		};

		//!@ Constructor
		Vec4() = default;
		Vec4(Vec3<float> i_v, float i_w) : x(i_v.x), y(i_v.y), z(i_v.z), w(i_w) {}
		Vec4(float i_x, float i_y, float i_z, float i_w) : x(i_x), y(i_y), z(i_z), w(i_w) {}

		//!@ Operator with constant value
		friend Vec4 operator + (float t, Vec4 const& u) { Vec4 o_v; o_v.x = t + u.x; o_v.y = t + u.y; o_v.z = t + u.z; o_v.w = t + u.w; return o_v; }
		friend Vec4 operator - (float t, Vec4 const& u) { Vec4 o_v; o_v.x = t - u.x; o_v.y = t - u.y; o_v.z = t - u.z; o_v.w = t - u.w; return o_v; }
		friend Vec4 operator * (float t, Vec4 const& u) { Vec4 o_v; o_v.x = t * u.x; o_v.y = t * u.y; o_v.z = t * u.z; o_v.w = t * u.w; return o_v; }
		Vec4 operator / (float const t)  const { Vec4 o_v; o_v.x = x / t; o_v.y = y / t; o_v.z = z / t; o_v.w = w / t; return o_v; }

		template <typename U>
		explicit Vec4(Vec4<U> const& u) : x(static_cast<float>(u.x)), y(static_cast<float>(u.y)), z(static_cast<float>(u.z)), z(static_cast<float>(u.w)) {}
		template <typename U>
		explicit Vec4(Vec3<U> const& t) : x(t.x), y(t.y), z(t.z), w(0) {}

		Vec4<float> operator + (Vec4<float> const& i_v) const;
		Vec4<float> operator - (Vec4<float> const& i_v) const;
		Vec4<float> operator * (Vec4<float> const& i_v) const;
		Vec4<float> operator / (Vec4<float> const& i_v) const;
	};

} // <- namespace Math


typedef Math::Vec2<float>            Vec2f;

//typedef Math::Vec3<unsigned short>   Vec3us;
//typedef Math::Vec3<short>            Vec3s;
//typedef Math::Vec3<unsigned int>     Vec3ui;
//typedef Math::Vec3<int>              Vec3i;
typedef Math::Vec3<float>            Vec3f;
typedef Math::Vec3<double>           Vec3d;

typedef Math::Vec4<float>            Vec4f;
typedef Math::Vec4<double>           Vec4d;

#include "Vector.inl"
#include "Vector.intrinsic.inl"