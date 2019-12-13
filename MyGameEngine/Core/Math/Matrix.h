#pragma once

#include "Vector.h"

#include <math.h>

namespace Math
{
	template<typename T>
	class Matrix4
	{
	public:

		// Elements of the matrix are row-major:
		// [ 0, 1, 2, 3] 
		// [ 4, 5, 6, 7]  
		// [ 8, 9,10,11] 
		// [12,13,14,15] 
		union
		{
			T ele[16];
			Vec4<T> column;
			struct
			{
				T   ele_11, ele_12, ele_13, ele_14,
					ele_21, ele_22, ele_23, ele_24,
					ele_31, ele_32, ele_33, ele_34,
					ele_41, ele_42, ele_43, ele_44;
			};
		};

		Matrix4() = default;

		Matrix4<T> operator +(Matrix4<T> const & i_m) const;
		Matrix4<T> operator -(Matrix4<T> const & i_m) const;
		Matrix4<T> operator *(Matrix4<T> const & i_m) const;

		Vec4<T> operator + (Vec4<T> const & i_v) const;
		Vec4<T> operator - (Vec4<T> const & i_v) const;
		Vec4<T> operator * (Vec4<T> const & i_v) const;
	};


}