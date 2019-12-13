#include "Vector.h"

#ifdef _USEINTRINSIC_

namespace Math {

	///////////////////////////////////////////////
	// Vector3<float>
	///////////////////////////////////////////////
	Vec3<float> Vec3<float>::operator+ (Vec3<float> const& i_v) const 
	{
		Vec3<float> o_v;
		o_v.m_vec = _mm_add_ps(m_vec, i_v.m_vec);
		return o_v;
	}

	Vec3<float> Vec3<float>::operator- (Vec3<float> const& i_v) const
	{
		Vec3<float> o_v;
		o_v.m_vec = _mm_sub_ps(m_vec, i_v.m_vec);
		return o_v;
	}

	Vec3<float> Vec3<float>::operator* (Vec3<float> const& i_v) const
	{
		Vec3<float> o_v;
		o_v.m_vec = _mm_mul_ps(m_vec, i_v.m_vec);
		return o_v;
	}

	Vec3<float> Vec3<float>::operator/ (Vec3<float> const& i_v) const
	{
		Vec3<float> o_v;
		o_v.m_vec = _mm_div_ps(m_vec, i_v.m_vec);
		return o_v;
	}

	///////////////////////////////////////////////
	// Vector4<float>
	///////////////////////////////////////////////
	Vec4<float> Vec4<float>::operator+ (Vec4<float> const& i_v) const
	{
		Vec4<float> o_v;
		o_v.m_vec = _mm_add_ps(m_vec, i_v.m_vec);
		return o_v;
	}

	Vec4<float> Vec4<float>::operator- (Vec4<float> const& i_v) const
	{
		Vec4<float> o_v;
		o_v.m_vec = _mm_sub_ps(m_vec, i_v.m_vec);
		return o_v;
	}

	Vec4<float> Vec4<float>::operator* (Vec4<float> const& i_v) const
	{
		Vec4<float> o_v;
		o_v.m_vec = _mm_mul_ps(m_vec, i_v.m_vec);
		return o_v;
	}

	Vec4<float> Vec4<float>::operator/ (Vec4<float> const& i_v) const
	{
		Vec4<float> o_v;
		o_v.m_vec = _mm_div_ps(m_vec, i_v.m_vec);
		return o_v;
	}
}

#endif // _USEINTRINSIC_
