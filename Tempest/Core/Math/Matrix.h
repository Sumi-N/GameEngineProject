#pragma once

#include "Vector.h"

#include <math.h>

// Elements of the matrix are column-major:
// [ 0, 4,  8, 12]  //[0, 3, 6]
// [ 1, 5,  9, 13]  //[1, 4, 7]
// [ 2, 6, 10, 14]  //[2, 5, 8]
// [ 3, 7, 11, 15] 

namespace Math
{
	template<typename T>
	class Matrix4
	{
	public:
		union
		{
			T ele[16];
			Vec4<T> column[4];
		};

		Matrix4();		
		Matrix4(T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T);

		Matrix4<T> operator +(Matrix4<T> const & i_m) const;
		Matrix4<T> operator -(Matrix4<T> const & i_m) const;
		Matrix4<T> operator *(Matrix4<T> const & i_m) const;
		Matrix4<T> operator /(T const& i_v) const;
		Matrix4<T>& operator = (Matrix4<T> const& i_m);

		Vec3<T> operator * (Vec3<T> const & i_v) const;
		Vec4<T> operator * (Vec4<T> const & i_v) const;

		void Transpose();
		void Inverse();

		static Matrix4<T> Roll (T const i_a);
		static Matrix4<T> Pitch(T const i_a);
		static Matrix4<T> Yaw  (T const i_a);

		static Matrix4<T> LookAt(Vec3<T> i_pos, Vec3<T> i_target, Vec3<T> i_upvec);
		static Matrix4<T> Perspective(T i_fov, T i_aspectratio, T i_near, T i_far);
		static Matrix4<T> Orthographic(T i_left, T i_right, T i_bottom, T i_top, T i_near, T i_far);

		static Matrix4<T> Transpose(Matrix4<T> i_m);
		static Matrix4<T> Inverse  (Matrix4<T> i_m);
		static Matrix4<T> Translate(Vec3<T> i_v);
		static Matrix4<T> EulerAngleZYX(T x, T y, T z);
		static Matrix4<T> Scale(Vec3<T> i_v);

		static Matrix4<T> TruncateToMat3(Matrix4<T> i_m);
	};

	//template<typename T>
	//class Matrix3
	//{
	//public:
	//	union
	//	{
	//		T ele[16];
	//		Vec3<T> column[3];
	//	};

	//	Matrix3();
	//};
}

typedef Math::Matrix4<float> Mat4f;


#include "Matrix.inl"
#include "Matrix.intrinsic.inl"