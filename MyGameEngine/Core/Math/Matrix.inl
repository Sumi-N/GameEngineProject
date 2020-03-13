#include "Matrix.h"

namespace Math {

	template<typename T>
	inline Matrix4<T> Matrix4<T>::operator*(Matrix4<T> const& i_m) const
	{
		Matrix4 o_m;

		o_m.ele[0]  = ele[0]  * i_m.ele[0] + ele[1]  * i_m.ele[4] + ele[2]  * i_m.ele[8]  + ele[3]  * i_m.ele[12];
		o_m.ele[1]  = ele[0]  * i_m.ele[1] + ele[1]  * i_m.ele[5] + ele[2]  * i_m.ele[9]  + ele[3]  * i_m.ele[13];
		o_m.ele[2]  = ele[0]  * i_m.ele[2] + ele[1]  * i_m.ele[6] + ele[2]  * i_m.ele[10] + ele[3]  * i_m.ele[14];
		o_m.ele[3]  = ele[0]  * i_m.ele[3] + ele[1]  * i_m.ele[7] + ele[2]  * i_m.ele[11] + ele[3]  * i_m.ele[15];
		o_m.ele[4]  = ele[4]  * i_m.ele[0] + ele[5]  * i_m.ele[4] + ele[6]  * i_m.ele[8]  + ele[7]  * i_m.ele[12];
		o_m.ele[5]  = ele[4]  * i_m.ele[1] + ele[5]  * i_m.ele[5] + ele[6]  * i_m.ele[9]  + ele[7]  * i_m.ele[13];
		o_m.ele[6]  = ele[4]  * i_m.ele[2] + ele[5]  * i_m.ele[6] + ele[6]  * i_m.ele[10] + ele[7]  * i_m.ele[14];
		o_m.ele[7]  = ele[4]  * i_m.ele[3] + ele[5]  * i_m.ele[7] + ele[6]  * i_m.ele[11] + ele[7]  * i_m.ele[15];
		o_m.ele[8]  = ele[8]  * i_m.ele[0] + ele[9]  * i_m.ele[4] + ele[10] * i_m.ele[8]  + ele[11] * i_m.ele[12];
		o_m.ele[9]  = ele[8]  * i_m.ele[1] + ele[9]  * i_m.ele[5] + ele[10] * i_m.ele[9]  + ele[11] * i_m.ele[13];
		o_m.ele[10] = ele[8]  * i_m.ele[2] + ele[9]  * i_m.ele[6] + ele[10] * i_m.ele[10] + ele[11] * i_m.ele[14];
		o_m.ele[11] = ele[8]  * i_m.ele[3] + ele[9]  * i_m.ele[7] + ele[10] * i_m.ele[11] + ele[11] * i_m.ele[15];
		o_m.ele[12] = ele[12] * i_m.ele[0] + ele[13] * i_m.ele[4] + ele[14] * i_m.ele[8]  + ele[15] * i_m.ele[12];
		o_m.ele[13] = ele[12] * i_m.ele[1] + ele[13] * i_m.ele[5] + ele[14] * i_m.ele[9]  + ele[15] * i_m.ele[13];
		o_m.ele[14] = ele[12] * i_m.ele[2] + ele[13] * i_m.ele[6] + ele[14] * i_m.ele[10] + ele[15] * i_m.ele[14];
		o_m.ele[15] = ele[12] * i_m.ele[3] + ele[13] * i_m.ele[7] + ele[14] * i_m.ele[11] + ele[15] * i_m.ele[15];

		return o_m;
	}

	template<typename T>
	inline Vec3<T> Matrix4<T>::operator*(Vec3<T> const& i_v) const
	{
		Vec4<T> i_v4 = Vec4<T>(i_v);
		Vec3<T> o_v3 = Vec3<T>((*this) * i_v4);
		return o_v3;
	}

	template<typename T>
	inline Vec4<T> Matrix4<T>::operator*(Vec4<T> const& i_v) const
	{
		Vec4<T> o_v;
		o_v.x = ele[0]  * i_v.x + ele[1]  * i_v.y + ele[2]  * i_v.z + ele[3] *  i_v.w;
		o_v.y = ele[4]  * i_v.x + ele[5]  * i_v.y + ele[6]  * i_v.z + ele[7] *  i_v.w;
		o_v.z = ele[8]  * i_v.x + ele[9]  * i_v.y + ele[10] * i_v.z + ele[11] * i_v.w;
		o_v.w = ele[12] * i_v.x + ele[13] * i_v.y + ele[14] * i_v.z + ele[15] * i_v.w;
		return o_v;
	}

	template<typename T>
	inline void Math::Matrix4<T>::Transpose() const
	{
		T tmp = ele[4];		ele[4] = ele[1];		ele[1] = tmp;
		tmp = ele[2];		ele[2] = ele[8];		ele[8] = tmp;
		tmp = ele[3];		ele[3] = ele[12];		ele[12] = tmp;
		tmp = ele[6];		ele[6] = ele[9];		ele[9] = tmp;
		tmp = ele[7];		ele[7] = ele[13];		ele[13] = tmp;
		tmp = ele[14];		ele[14] = ele[11];		ele[11] = tmp;
	}

	template<typename T>
	inline void Math::Matrix4<T>::Inverse() const
	{
		T absvalue = ele[0] * (ele[5] * ele[10] * ele[15] + ele[6] * ele[11] * ele[13] + ele[7] * ele[9] * ele[14] - ele[7] * ele[10] * ele[13] - ele[6] * ele[9] * ele[15] - ele[5] * ele[11] * ele[14])
			           - ele[4] * (ele[1] * ele[10] * ele[15] + ele[2] * ele[11] * ele[13] + ele[3] * ele[9] * ele[14] - ele[3] * ele[10] * ele[13] - ele[2] * ele[9] * ele[15] - ele[1] * ele[11] * ele[14])
			           + ele[8] * (ele[1] * ele[6]  * ele[15] + ele[2] * ele[7]  * ele[13] + ele[3] * ele[5] * ele[14] - ele[3] * ele[6]  * ele[13] - ele[2] * ele[5] * ele[15] - ele[1] * ele[7]  * ele[14]) 
			           -ele[12] * (ele[1] * ele[6]  * ele[11] + ele[2] * ele[7]  * ele[9]  + ele[3] * ele[5] * ele[10] - ele[3] * ele[6]  * ele[9]  - ele[2] * ele[5] * ele[11] - ele[1] * ele[7]  * ele[10]);

		assert(absvalue != 0);

		Matrix4 tmp;

		tmp.ele[0]  = ele[5] * ele[10] * ele[15] + ele[6] * ele[11] * ele[13] + ele[7] * ele[9] * ele[14] - ele[7] * ele[10] * ele[13] - ele[6] * ele[9] * ele[15] - ele[5] * ele[11] * ele[14];
		tmp.ele[1]  = ele[4] * ele[10] * ele[15] + ele[6] * ele[11] * ele[12] + ele[7] * ele[8] * ele[14] - ele[7] * ele[10] * ele[12] - ele[6] * ele[8] * ele[15] - ele[4] * ele[11] * ele[14];
		tmp.ele[2]  = ele[4] * ele[9]  * ele[15] + ele[5] * ele[11] * ele[12] + ele[7] * ele[8] * ele[13] - ele[7] * ele[9]  * ele[12] - ele[5] * ele[8] * ele[15] - ele[4] * ele[11] * ele[13];
		tmp.ele[3]  = ele[4] * ele[9]  * ele[14] + ele[5] * ele[10] * ele[12] + ele[6] * ele[8] * ele[13] - ele[6] * ele[9]  * ele[12] - ele[5] * ele[8] * ele[14] - ele[4] * ele[10] * ele[13];

		tmp.ele[4]  = ele[1] * ele[10] * ele[15] + ele[2] * ele[11] * ele[13] + ele[3] * ele[9] * ele[14] - ele[3] * ele[10] * ele[13] - ele[2] * ele[9] * ele[15] - ele[1] * ele[11] * ele[14];
		tmp.ele[5]  = ele[0] * ele[10] * ele[15] + ele[2] * ele[11] * ele[12] + ele[3] * ele[8] * ele[14] - ele[3] * ele[10] * ele[12] - ele[2] * ele[8] * ele[15] - ele[0] * ele[11] * ele[14];
		tmp.ele[6]  = ele[0] * ele[9]  * ele[15] + ele[1] * ele[11] * ele[12] + ele[3] * ele[8] * ele[13] - ele[3] * ele[9]  * ele[12] - ele[1] * ele[8] * ele[15] - ele[0] * ele[11] * ele[13];
		tmp.ele[7]  = ele[0] * ele[9]  * ele[14] + ele[1] * ele[10] * ele[12] + ele[2] * ele[8] * ele[13] - ele[2] * ele[9]  * ele[12] - ele[1] * ele[8] * ele[14] - ele[0] * ele[10] * ele[13];

		tmp.ele[8]  = ele[1] * ele[6]  * ele[15] + ele[2] * ele[7]  * ele[13] + ele[3] * ele[5] * ele[14] - ele[3] * ele[6]  * ele[13] - ele[2] * ele[5] * ele[15] - ele[1] * ele[7]  * ele[14];
		tmp.ele[9]  = ele[0] * ele[6]  * ele[15] + ele[2] * ele[7]  * ele[12] + ele[3] * ele[4] * ele[14] - ele[3] * ele[6]  * ele[12] - ele[2] * ele[4] * ele[15] - ele[0] * ele[7]  * ele[14];
		tmp.ele[10] = ele[0] * ele[5]  * ele[15] + ele[1] * ele[7]  * ele[12] + ele[3] * ele[4] * ele[13] - ele[3] * ele[5]  * ele[12] - ele[1] * ele[4] * ele[15] - ele[0] * ele[7]  * ele[13];
		tmp.ele[11] = ele[0] * ele[5]  * ele[14] + ele[1] * ele[6]  * ele[12] + ele[2] * ele[4] * ele[13] - ele[2] * ele[5]  * ele[12] - ele[1] * ele[4] * ele[14] - ele[0] * ele[6]  * ele[13];

		tmp.ele[12] = ele[1] * ele[6]  * ele[11] + ele[2] * ele[7]  * ele[9]  + ele[3] * ele[5] * ele[10] - ele[3] * ele[6]  * ele[9] - ele[2]  * ele[5] * ele[11] - ele[1] * ele[7]  * ele[10];
		tmp.ele[13] = ele[0] * ele[6]  * ele[11] + ele[2] * ele[7]  * ele[8]  + ele[3] * ele[4] * ele[10] - ele[3] * ele[6]  * ele[8] - ele[2]  * ele[4] * ele[11] - ele[0] * ele[7]  * ele[10];
		tmp.ele[14] = ele[0] * ele[5]  * ele[11] + ele[1] * ele[7]  * ele[8]  + ele[3] * ele[4] * ele[9]  - ele[3] * ele[5]  * ele[8] - ele[1]  * ele[4] * ele[11] - ele[0] * ele[7]  * ele[9];
		tmp.ele[15] = ele[0] * ele[5]  * ele[10] + ele[1] * ele[6]  * ele[8]  + ele[2] * ele[4] * ele[9]  - ele[2] * ele[5]  * ele[8] - ele[1]  * ele[4] * ele[10] - ele[0] * ele[6]  * ele[9];

		tmp.ele[1]  = -1 * tmp.ele[1];
		tmp.ele[3]  = -1 * tmp.ele[3];
		tmp.ele[4]  = -1 * tmp.ele[4];
		tmp.ele[6]  = -1 * tmp.ele[6];
		tmp.ele[9]  = -1 * tmp.ele[9];
		tmp.ele[11] = -1 * tmp.ele[11];
		tmp.ele[12] = -1 * tmp.ele[12];
		tmp.ele[14] = -1 * tmp.ele[14];

		tmp.Transpose();
		*this = tmp / absvalue;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Roll(T const i_a)
	{
		Matrix4 o_m;
		float radian = i_a * 2 * static_cast<T>(Math::Pi()) / 360;
		o_m.ele[5] = cosf(radian);
		o_m.ele[6] = -sinf(radian);
		o_m.ele[9] = sinf(radian);
		o_m.ele[10] = cosf(radian);
		o_m.ele[0] = 1;
		o_m.ele[15] = 1;

		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Pitch(T const i_a)
	{
		Matrix4 o_m;
		float radian = i_a * 2 * static_cast<T>(Math::Pi()) / 360;
		o_m.ele[0] = cosf(radian);
		o_m.ele[2] = sinf(radian);
		o_m.ele[8] = -sinf(radian);
		o_m.ele[10] = cosf(radian);
		o_m.ele[5] = 1;
		o_m.ele[15] = 1;

		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Yaw(T const i_a)
	{
		Matrix4 o_m;
		float radian = i_a * 2 * static_cast<T>(Math::Pi<T>()) / 360;
		o_m.ele[0] = cosf(radian);
		o_m.ele[1] = -sinf(radian);
		o_m.ele[4] = sinf(radian);
		o_m.ele[5] = cosf(radian);
		o_m.ele[10] = 1;
		o_m.ele[15] = 1;

		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::LookAt(Vec3<T> i_pos, Vec3<T> i_target, Vec3<T> i_upvec) 
	{
		Vec4<T> forwardvec = Vec4<T>(Vec3<T>::Normalize(i_target - i_pos), 0);
		Vec4<T> rightvec = Vec4<T>(Vec3<T>::Normalize(Vec3<T>(forwardvec).Cross(i_upvec)), 0);
		Vec4<T> upvec = Vec4<T>(Vec3<T>::Normalize(i_upvec), 0);
		Vec4<T> posvec = Vec4<T>(i_pos, 1);

		Matrix4 o_m;
		o_m.column[0] = rightvec;
		o_m.column[1] = upvec;
		o_m.column[2] = forwardvec;
		o_m.column[3] = posvec;

		return o_m;
	}
	template<typename T>
	inline Matrix4<T> Matrix4<T>::Perspective(T i_fov, T i_aspectratio, T i_near, T i_far)
	{
		T range = i_near - i_far;
		T tanhalffov = static_cast<T>(i_fov * M_PI / 2.0 * 180);

		Matrix4 o_m;

		o_m.ele[0] = static_cast<T>(1.0 / tanhalffov * i_aspectratio);
		o_m.ele[1] = 0;
		o_m.ele[2] = 0;
		o_m.ele[3] = 0;

		o_m.ele[0] = 0;
		o_m.ele[1] = static_cast<T>(1.0 / tanhalffov);
		o_m.ele[2] = 0;
		o_m.ele[3] = 0;

		o_m.ele[0] = 0;
		o_m.ele[1] = 0;
		o_m.ele[2] = static_cast<T>((-1 * i_near + -1 * i_far) / range);
		o_m.ele[3] = static_cast <T>(2.0 * i_far * i_near / range);

		o_m.ele[0] = 0;
		o_m.ele[1] = 0;
		o_m.ele[2] = 1.0;
		o_m.ele[3] = 0;

		return o_m;
	}
}

#ifndef _USEINTRINSIC_

namespace Math 
{
	template<typename T>
	inline Matrix4<T> Matrix4<T>::operator+(Matrix4<T> const& i_m) const
	{
		Matrix4 o_m;
		for (int i = 0; i < 16; i++)
		{
			o_m.ele[i] = this->ele[i] + i_m.ele[i];
		}
		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::operator-(Matrix4<T> const& i_m) const
	{
		Matrix4 o_m;
		for (int i = 0; i < 16; i++)
		{
			o_m.ele[i] = this->ele[i] - i_m.ele[i];
		}
		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Math::Matrix4<T>::operator/(T const& i_v) const
	{
		Matrix4 o_m;
		for (int i = 0; i < 16; i++)
		{
			o_m.ele[i] = this->ele[i] / i_v;
		}
		return o_m;
	}
}

#endif // !_USEINTRINSIC_