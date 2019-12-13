#include "Matrix.h"

namespace Math{

	template<typename T>
	Matrix4<T> Matrix4<T>::operator+(Matrix4<T> const & i_m) const
	{
		Matrix4 o_m;

		return o_m;
	}

	template<typename T>
	Matrix4<T> Matrix4<T>::operator*(Matrix4<T> const & i_m) const 
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
	Vec4<T> Matrix4<T>::operator*(Vec4<T> const & i_v) const
	{

		return Vec4<T>();
	}
}

#ifdef _USEINTRINSIC_

#endif // !_USEINTRINSIC_