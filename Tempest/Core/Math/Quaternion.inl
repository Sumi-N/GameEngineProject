#include "Quaternion.h"
#pragma once

namespace Math
{
	template<typename T>
	inline Math::Quaternion<T>::Quaternion(): x(1), y(0), z(0), w(0) {}

	template<typename T>
	inline Math::Quaternion<T>::Quaternion(T const& i_r, Vec3<T> const& i_a)
	: x(cosf(i_r/2)), y(i_a.x * sinf(i_r/2)), z(i_a.y * sinf(i_r/2)), w(i_a.z * sinf(i_r/2)) {}

	template<typename T>
	inline Math::Quaternion<T>::Quaternion(T const& i_x, T const& i_y, T const& i_z, T const& i_w)
	: x(i_x), y(i_y), z(i_z), w(i_w) {}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator+(Quaternion<T> const& i_q) const
	{
		return Quaternion<T>(x + i_q.x, y + i_q.y, z + i_q.z, w + i_q.w);
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator-(Quaternion<T> const& i_q) const
	{
		return Quaternion<T>(x - i_q.x, y - i_q.y, z - i_q.z, w - i_q.w);
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator*(Quaternion<T> const& i_q) const
	{
		Vec3<T> vec1(y, z, w);
		Vec3<T> vec2(i_q.y, i_q.z, i_q.w);

		Vec3<T> imaginary = x * vec2 + i_q.x * vec1 + vec1.Cross(vec2);

		return Quaternion(x * i_q.x - vec1.Dot(vec2), imaginary.x, imaginary.y, imaginary.z);
	}

	template<typename T>
	inline Vec3<T>      Quaternion<T>::operator*(Vec3<T> const& i_v) 
	{
		Quaternion<T> p(0, i_v.x, i_v.y, i_v.z);
		Normalize();
		Quaternion q = (*this);
		Quaternion q_inverse = q.Inverse();

		p = q * p * q_inverse;
		return Vec3<T>(p.y, p.z, p.w);
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::Conjugate() const
	{
		return Quaternion<T>(x, -1 * y, -1 * z, -1 * w);
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::Inverse() const
	{
		Quaternion conjugate = Conjugate();
		conjugate.Normalize();
		return conjugate;
	}

	template<typename T>
	inline T Quaternion<T>::Dot(Quaternion<T> const& i_q) const
	{
		return x * i_q.x + y * i_q.y + z * i_q.z +w * i_q.w;
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::AngleAxis(T const& angle, Vec3<T> const& axis)
	{
		return Quaternion<T>(angle, axis);
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::EulerToQuaternion(T const& i_x, T const& i_y, T const& i_z)
	{
		//https://www.kazetest.com/vcmemo/quaternion/quaternion.html
		T x = 2 * i_x *  static_cast<T>(M_PI) / 360;
		T y = 2 * i_y *static_cast<T>(M_PI) / 360;
		T z = 2 * i_z * static_cast<T>(M_PI) / 360;

		T roll   = x * 0.5f;
		T pitch = y * 0.5f;
		T yaw  = z * 0.5f;

		T cosRollOver2 = static_cast<T>(cosf(roll));
		T sinRollOver2 = static_cast<T>(sinf(roll));

		T cosPitchOver2 = static_cast<T>(cosf(pitch));
		T sinPitchOver2 = static_cast<T>(sinf(pitch));

		T cosYawOver2 = static_cast<T>(cosf(yaw));
		T sinYawOver2 = static_cast<T>(sinf(yaw));

		Quaternion result;

		result.x = cosRollOver2 * cosPitchOver2 * cosYawOver2 + sinRollOver2 * sinYawOver2 * sinPitchOver2;
		result.y = sinRollOver2 * cosPitchOver2 * cosYawOver2 - cosRollOver2 * sinPitchOver2 * sinYawOver2;
		result.z = cosRollOver2 * sinPitchOver2 * cosYawOver2 + sinRollOver2 * cosPitchOver2 * sinYawOver2;
		result.w = cosRollOver2 * cosPitchOver2 * sinYawOver2 - sinRollOver2 * sinPitchOver2 * cosYawOver2;

		return result;
	}

	template<typename T>
	inline Vec3<T> Quaternion<T>::QuaternionToEuler(Quaternion<T> q)
	{
		//https://www.kazetest.com/vcmemo/quaternion/quaternion.htm
		Vec3<T> euler;
		
		// if the input quaternion is normalized, this is exactly one. Otherwise, this acts as a correction factor for the quaternion's not-normalizedness
		T unit = (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w);
		
		// this will have a magnitude of 0.5 or greater if and only if this is a singularity case
		T test = q.y * q.x - q.z * q.w;
		
		if (test > 0.4995f * unit) // singularity at north pole
		{
			DEBUG_ASSERT(false);

			/*euler.x = M_PI / 2;
			euler.z = atan2(q.z, q.y);
			euler.y = 0;*/
		}
		else if (test < -0.4995f * unit) // singularity at south pole
		{
			DEBUG_ASSERT(false);

			//euler.x = -M_PI / 2;
			//euler.z = atan2(q.z, q.y);
			//euler.y = 0;
		}
		else // no singularity - this is the majority of cases
		{
			euler.x = atan2(2 * q.x * q.y + 2 * q.z * q.w, 1 - 2 * (q.y * q.y + q.z * q.z));
			euler.y = asin(2 * (q.x * q.z - q.y * q.w));
			euler.z = atan2(2 * q.x * q.w + 2 * q.y * q.z, 1 - 2 * (q.z * q.z + q.w * q.w));
		}
		
		// all the math so far has been done in radians. Before returning, we convert to degrees...
		euler *= 180 / static_cast<float>(M_PI);
		
		return euler;
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::Lerp(Quaternion<T> const& i_a, Quaternion<T> const& i_b, T i_t)
	{
		if (i_t > static_cast<T>(1) || i_t < static_cast<T>(0))
		{
			DEBUG_ASSERT(false);
		}

		Quaternion<T> c = i_b;
		T cos_theta = i_a.Dot(i_b);

		if (cos_theta < static_cast<T>(0))
		{
			c = -1 * i_b;			
		}

		return (static_cast<T>(1) - i_t) * i_a + i_t * c;
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::Slerp(Quaternion<T> const& i_a, Quaternion<T> const& i_b, T i_t)
	{
		if (i_t > static_cast<T>(1) || i_t < static_cast<T>(0))
		{
			DEBUG_ASSERT(false);
		}

		Quaternion<T> c = i_b;
		T cos_theta = i_a.Dot(i_b);

		if (cos_theta < static_cast<T>(0))
		{
			c = -1 * i_b;
			cos_theta = -1 * cos_theta;
		}

		//From quaternion_common.inl in glm
		//if (cos_theta > static_cast<T>(1) - epsilon<T>())
		//{
		//	// Linear interpolation
		//	return qua<T, Q>(
		//		mix(x.w, z.w, a),
		//		mix(x.x, z.x, a),
		//		mix(x.y, z.y, a),
		//		mix(x.z, z.z, a));
		//}
		//else
		{
			T angle = acos(cos_theta);
			return (sin((static_cast<T>(1) - i_t) * angle) * i_a + sin(i_t * angle) * c) / sin(angle);
		}
	}


	template<typename T>
	inline Matrix4<T> Quaternion<T>::QuaternionToRotationMatix(Quaternion<T> i_q)
	{
		T m[16] = {};
		m[0] = static_cast<T>(1) - static_cast<T>(2) * (i_q.y * i_q.y + i_q.z * i_q.z);
		m[1] = static_cast<T>(2) * (i_q.x * i_q.y + i_q.z * i_q.w);
		m[2] = static_cast<T>(2) * (i_q.x * i_q.z - i_q.y * i_q.w);
		m[3] = static_cast<T>(0);

		m[4] = static_cast<T>(2) * (i_q.x * i_q.y - i_q.z * i_q.w);
		m[5] = static_cast<T>(1) - static_cast<T>(2) * (i_q.x * i_q.x + i_q.z * i_q.z);
		m[6] = static_cast<T>(2) * (i_q.y * i_q.z + i_q.x * i_q.w);
		m[7] = static_cast<T>(0);

		m[8] = static_cast<T>(2) * (i_q.x * i_q.z + i_q.w * i_q.y);
		m[9] = static_cast<T>(2) * (i_q.y * i_q.z - i_q.x * i_q.w);
		m[10] = static_cast<T>(1) - static_cast<T>(2) * (i_q.x * i_q.x + i_q.y * i_q.y);
		m[11] = static_cast<T>(0);

		m[12] = static_cast<T>(0);
		m[13] = static_cast<T>(0);
		m[14] = static_cast<T>(0);
		m[15] = static_cast<T>(1);

		return Matrix4<T>(m);
	}
}
