#ifndef _USEINTRINSIC_

namespace Math {

	//---------------------------------------------
	// Vector3<float>
	//---------------------------------------------
	inline Vec3<float> Vec3<float>::operator+ (Vec3<float> const& i_v) const
	{
		Vec3<float> o_v;
		o_v = Vec3(this->x + i_v.x, this->y + i_v.y, z + i_v.z);
		return o_v;
	}

	inline Vec3<float> Vec3<float>::operator- (Vec3<float> const& i_v) const
	{
		Vec3<float> o_v;
		o_v = Vec3(this->x - i_v.x, this->y - i_v.y, z - i_v.z);
		return o_v;
	}

	inline Vec3<float> Vec3<float>::operator* (Vec3<float> const& i_v) const
	{
		Vec3<float> o_v;
		o_v = Vec3(this->x * i_v.x, this->y * i_v.y, z * i_v.z);
		return o_v;
	}

	inline Vec3<float> Vec3<float>::operator/ (Vec3<float> const& i_v) const
	{
		Vec3<float> o_v;
		o_v = Vec3(this->x / i_v.x, this->y / i_v.y, z / i_v.z);
		return o_v;
	}

	//---------------------------------------------
	// Vector4<float>
	//---------------------------------------------

	inline Vec4<float> Vec4<float>::operator+ (Vec4<float> const& i_v) const
	{
		Vec4<float> o_v;
		o_v = Vec4(this->x + i_v.x, this->y + i_v.y, z + i_v.z, this->w + i_v.w);
		return o_v;
	}

	inline Vec4<float> Vec4<float>::operator- (Vec4<float> const& i_v) const
	{
		Vec4<float> o_v;
		o_v = Vec4(this->x - i_v.x, this->y - i_v.y, z - i_v.z, this->w - i_v.w);
		return o_v;
	}

	inline Vec4<float> Vec4<float>::operator* (Vec4<float> const& i_v) const
	{
		Vec4<float> o_v;
		o_v = Vec4(this->x * i_v.x, this->y * i_v.y, z * i_v.z, this->w * i_v.w);
		return o_v;
	}

	inline Vec4<float> Vec4<float>::operator/ (Vec4<float> const& i_v) const
	{
		Vec4<float> o_v;
		o_v = Vec4(this->x / i_v.x, this->y / i_v.y, z * i_v.z, this->w / i_v.w);
		return o_v;
	}

	inline Vec4<float>& Vec4<float>::operator= (Vec4<float> const& i_v)
	{
		this->x = i_v.x;
		this->y = i_v.y;
		this->z = i_v.z;
		this->w = i_v.w;
		return *this;
	}
}

#endif // !_USEINTRINSIC_
