#ifdef _USEINTRINSIC_

namespace Math
{
	template<typename T>
	inline Matrix4<T> Matrix4<T>::operator+(Matrix4<T> const& i_m) const
	{
		Matrix4 o_m;

		__pragma(loop(ivdep))
		for (int i = 0; i < 16; i++)
			o_m.ele[i] = this->ele[i] + i_m.ele[i];
		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::operator-(Matrix4<T> const& i_m) const
	{
		Matrix4 o_m;

		__pragma(loop(ivdep))
		for (int i = 0; i < 16; i++)
			o_m.ele[i] = this->ele[i] - i_m.ele[i];
		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Math::Matrix4<T>::operator/(T const& i_v) const
	{
		Matrix4 o_m;

		__pragma(loop(ivdep))
		for (int i = 0; i < 16; i++)
			o_m.ele[i] = this->ele[i] / i_v;
		return o_m;
	}
}
#endif // !_USEINTRINSIC_