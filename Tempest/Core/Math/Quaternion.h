#pragma once

#include "Define.h"
#include "Vector.h"
#include "Matrix.h"


namespace Math
{
	template<typename T>
	class Quaternion
	{
	public:
		// x is a real number part, and y, z ,w are imaginary number part
		// Quaternion q = x + y * i + z * j + w * k;
		T x, y, z, w;
		
		Quaternion();
		Quaternion(T const&, Vec3<T> const&);
		Quaternion(T const&, T const&, T const&, T const&);

		Quaternion(Quaternion const& i_q) :x(i_q.x), y(i_q.y), z(i_q.z), w(i_q.w) {}

		friend Quaternion operator * (T t, Quaternion const& q) { return Quaternion (t * q.x, t * q.y, t * q.z, t * q.w);}
		       Quaternion operator / (T const t) const { Quaternion o_q; o_q.x = x / t; o_q.y = y / t; o_q.z = z / t; o_q.w = w / t; return o_q;}

		Quaternion<T> operator +(Quaternion<T> const& i_q) const;
		Quaternion<T> operator -(Quaternion<T> const& i_q) const;
		Quaternion<T> operator *(Quaternion<T> const& i_q) const;
		Vec3<T>       operator *(Vec3<T> const& i_v);

		//!@ Assignment operators
		Quaternion const& operator += (T    const  t) { x += t; y += t; z += t; w += t; return *this; }
		Quaternion const& operator -= (T    const  t) { x -= t; y -= t; z -= t; w -= t; return *this; }
		Quaternion const& operator *= (T    const  t) { x *= t; y *= t; z *= t; w *= t; return *this; }
		Quaternion const& operator /= (T    const  t) { x /= t; y /= t; z /= t; w /= t; return *this; }

		void Normalize ()       { *this /= Length(); }
		T    Length() const { return sqrt(static_cast<T>(x)* static_cast<T>(x) + static_cast<T>(y)* static_cast<T>(y) + static_cast<T>(z)* static_cast<T>(z) + static_cast<T>(w)* static_cast<T>(w)); }
		Quaternion<T> Conjugate() const;
		Quaternion<T> Inverse() const;
		float Dot(Quaternion<T> i_q);

		static Quaternion<T> AngleAxis(float const&, Vec3<T> const&);
		static Quaternion<T> EulerToQuaternion(float const&, float const&, float const&);
		static Vec3<T> QuaternionToEuler(Quaternion<T>);
		static Quaternion<T> Lerp(Quaternion<T>, Quaternion<T>, float);

		static Matrix4<T> QuaternionToRotationMatix(Quaternion<T>);
	};
}

typedef Math::Quaternion<float> Quaternionf;

#include "Quaternion.inl"