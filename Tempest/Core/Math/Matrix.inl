
namespace Math {

	// Forward Declaration
	template<typename T> class Quaternion;

	template<typename T>
	inline Matrix4<T>::Matrix4()
	{
		this->ele[0]  = static_cast<T>(1); this->ele[1] = 0; this->ele[2] = 0; this->ele[3] = 0;
		this->ele[4]  = 0; this->ele[5] = static_cast<T>(1); this->ele[6] = 0; this->ele[7] = 0;
		this->ele[8]  = 0; this->ele[9] = 0; this->ele[10] = static_cast<T>(1); this->ele[11] = 0;
		this->ele[12] = 0; this->ele[13] = 0; this->ele[14] = 0; this->ele[15] = static_cast<T>(1);
	}

	template<typename T>
	inline Matrix4<T>::Matrix4(T* i_m)
	{
		this->ele[0]  = i_m[0]; this->ele[1] = i_m[1]; this->ele[2] = i_m[2]; this->ele[3] = i_m[3];
		this->ele[4]  = i_m[4]; this->ele[5] = i_m[5]; this->ele[6] = i_m[6]; this->ele[7] = i_m[7];
		this->ele[8]  = i_m[8]; this->ele[9] = i_m[9]; this->ele[10] = i_m[10]; this->ele[11] = i_m[11];
		this->ele[12] = i_m[12]; this->ele[13] = i_m[13]; this->ele[14] = i_m[14]; this->ele[15] = i_m[15];
	}

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
	inline Matrix4<T> Matrix4<T>::operator*(Matrix4<T> const& i_m) const
	{
		Matrix4 o_m;

		o_m.ele[0]  = ele[0] * i_m.ele[0]  + ele[4]  * i_m.ele[1]  + ele[8]  * i_m.ele[2]  + ele[12]  * i_m.ele[3];
		o_m.ele[4]  = ele[0] * i_m.ele[4]  + ele[4]  * i_m.ele[5]  + ele[8]  * i_m.ele[6]  + ele[12]  * i_m.ele[7];
		o_m.ele[8]  = ele[0] * i_m.ele[8]  + ele[4]  * i_m.ele[9]  + ele[8]  * i_m.ele[10] + ele[12]  * i_m.ele[11];
		o_m.ele[12] = ele[0] * i_m.ele[12] + ele[4]  * i_m.ele[13] + ele[8]  * i_m.ele[14] + ele[12]  * i_m.ele[15];
		o_m.ele[1]  = ele[1] * i_m.ele[0]  + ele[5]  * i_m.ele[1]  + ele[9]  * i_m.ele[2]  + ele[13]  * i_m.ele[3];
		o_m.ele[5]  = ele[1] * i_m.ele[4]  + ele[5]  * i_m.ele[5]  + ele[9]  * i_m.ele[6]  + ele[13]  * i_m.ele[7];
		o_m.ele[9]  = ele[1] * i_m.ele[8]  + ele[5]  * i_m.ele[9]  + ele[9]  * i_m.ele[10] + ele[13]  * i_m.ele[11];
		o_m.ele[13] = ele[1] * i_m.ele[12] + ele[5]  * i_m.ele[13] + ele[9]  * i_m.ele[14] + ele[13]  * i_m.ele[15];
		o_m.ele[2]  = ele[2] * i_m.ele[0]  + ele[6]  * i_m.ele[1]  + ele[10] * i_m.ele[2]  + ele[14]  * i_m.ele[3];
		o_m.ele[6]  = ele[2] * i_m.ele[4]  + ele[6]  * i_m.ele[5]  + ele[10] * i_m.ele[6]  + ele[14]  * i_m.ele[7];
		o_m.ele[10] = ele[2] * i_m.ele[8]  + ele[6]  * i_m.ele[9]  + ele[10] * i_m.ele[10] + ele[14]  * i_m.ele[11];
		o_m.ele[14] = ele[2] * i_m.ele[12] + ele[6]  * i_m.ele[13] + ele[10] * i_m.ele[14] + ele[14]  * i_m.ele[15];
		o_m.ele[3]  = ele[3] * i_m.ele[0]  + ele[7]  * i_m.ele[1]  + ele[11] * i_m.ele[2]  + ele[15]  * i_m.ele[3];
		o_m.ele[7]  = ele[3] * i_m.ele[4]  + ele[7]  * i_m.ele[5]  + ele[11] * i_m.ele[6]  + ele[15]  * i_m.ele[7];
		o_m.ele[11] = ele[3] * i_m.ele[8]  + ele[7]  * i_m.ele[9]  + ele[11] * i_m.ele[10] + ele[15]  * i_m.ele[11];
		o_m.ele[15] = ele[3] * i_m.ele[12] + ele[7]  * i_m.ele[13] + ele[11] * i_m.ele[14] + ele[15]  * i_m.ele[15];

		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::operator/(T const& i_v) const
	{
		Matrix4 o_m;
		for (int i = 0; i < 16; i++)
		{
			o_m.ele[i] = this->ele[i] / i_v;
		}
		return o_m;
	}

	template<typename T>
	inline Matrix4<T>& Matrix4<T>::operator=(Matrix4<T> const& i_m)
	{
		for (int i = 0; i < 16; i++)
		{
			this->ele[i] = i_m.ele[i];
		}
		return *this;
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
		o_v.x = ele[0] * i_v.x + ele[4] * i_v.y + ele[8]  * i_v.z + ele[12] *  i_v.w;
		o_v.y = ele[1] * i_v.x + ele[5] * i_v.y + ele[9]  * i_v.z + ele[13] *  i_v.w;
		o_v.z = ele[2] * i_v.x + ele[6] * i_v.y + ele[10] * i_v.z + ele[14] * i_v.w;
		o_v.w = ele[3] * i_v.x + ele[7] * i_v.y + ele[11] * i_v.z + ele[15] * i_v.w;

		return o_v;
	}

	template<typename T>
	inline void Math::Matrix4<T>::Transpose() 
	{
		T tmp = ele[4];		ele[4] = ele[1];		ele[1] = tmp;
		tmp = ele[2];		ele[2] = ele[8];		ele[8] = tmp;
		tmp = ele[3];		ele[3] = ele[12];		ele[12] = tmp;
		tmp = ele[6];		ele[6] = ele[9];		ele[9] = tmp;
		tmp = ele[7];		ele[7] = ele[13];		ele[13] = tmp;
		tmp = ele[14];		ele[14] = ele[11];		ele[11] = tmp;
	}

	template<typename T>
	inline void Math::Matrix4<T>::Inverse() 
	{
		T absvalue = ele[0] * (ele[5] * ele[10] * ele[15] + ele[6] * ele[11] * ele[13] + ele[7] * ele[9] * ele[14] - ele[7] * ele[10] * ele[13] - ele[6] * ele[9] * ele[15] - ele[5] * ele[11] * ele[14])
			           - ele[4] * (ele[1] * ele[10] * ele[15] + ele[2] * ele[11] * ele[13] + ele[3] * ele[9] * ele[14] - ele[3] * ele[10] * ele[13] - ele[2] * ele[9] * ele[15] - ele[1] * ele[11] * ele[14])
			           + ele[8] * (ele[1] * ele[6]  * ele[15] + ele[2] * ele[7]  * ele[13] + ele[3] * ele[5] * ele[14] - ele[3] * ele[6]  * ele[13] - ele[2] * ele[5] * ele[15] - ele[1] * ele[7]  * ele[14]) 
			           -ele[12] * (ele[1] * ele[6]  * ele[11] + ele[2] * ele[7]  * ele[9]  + ele[3] * ele[5] * ele[10] - ele[3] * ele[6]  * ele[9]  - ele[2] * ele[5] * ele[11] - ele[1] * ele[7]  * ele[10]);

		DEBUG_ASSERT(absvalue != 0);

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
	inline Matrix4<T> Matrix4<T>::Zero()
	{
		Matrix4 o_m;

		o_m.ele[0] = o_m.ele[1] = o_m.ele[2] = o_m.ele[3] = static_cast<T>(0);
		o_m.ele[4] = o_m.ele[5] = o_m.ele[6] = o_m.ele[7] = static_cast<T>(0);
		o_m.ele[8] = o_m.ele[9] = o_m.ele[10] = o_m.ele[11] = static_cast<T>(0);
		o_m.ele[12] = o_m.ele[13] = o_m.ele[14] = o_m.ele[15] = static_cast<T>(0);

		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Roll(T const i_a)
	{
		Matrix4 o_m;
		float radian = i_a * 2 * static_cast<T>(M_PI) / 360;
		o_m.ele[5] = cosf(radian);
		o_m.ele[6] = sinf(radian);
		o_m.ele[9] = -sinf(radian);
		o_m.ele[10] = cosf(radian);
		o_m.ele[0] = 1;
		o_m.ele[15] = 1;

		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Pitch(T const i_a)
	{
		Matrix4 o_m;
		float radian = i_a * 2 * static_cast<T>(M_PI) / 360;
		o_m.ele[0] = cosf(radian);
		o_m.ele[2] = -sinf(radian);
		o_m.ele[8] = sinf(radian);
		o_m.ele[10] = cosf(radian);
		o_m.ele[5] = 1;
		o_m.ele[15] = 1;

		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Yaw(T const i_a)
	{
		Matrix4 o_m;
		float radian = i_a * 2 * static_cast<T>(M_PI) / 360;
		o_m.ele[0] = cosf(radian);
		o_m.ele[1] = sinf(radian);
		o_m.ele[4] = -sinf(radian);
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

		Matrix4 o_m;
		o_m.ele[0] = rightvec.x;
		o_m.ele[4] = rightvec.y;
		o_m.ele[8] = rightvec.z;
		o_m.ele[1] = upvec.x;
		o_m.ele[5] = upvec.y;
		o_m.ele[9] = upvec.z;
		o_m.ele[2] = -1 * forwardvec.x;
		o_m.ele[6] = -1 * forwardvec.y;
		o_m.ele[10] = -1 * forwardvec.z;
		o_m.ele[12] = -1 * Vec3<T>(rightvec).Dot(i_pos);
		o_m.ele[13] = -1 * Vec3<T>(upvec).Dot(i_pos);
		o_m.ele[14] = Vec3<T>(forwardvec).Dot(i_pos);

		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Perspective(T i_fov, T i_aspectratio, T i_near, T i_far)
	{
		T range = i_far - i_near;
		T tanhalffov = static_cast<T>(tan((i_fov * M_PI) / 360.0));

		Matrix4 o_m;

		o_m.ele[0] = static_cast<T>(1.0) / static_cast<T>(tanhalffov * i_aspectratio);

		o_m.ele[5] = static_cast<T>(1.0 / tanhalffov);

		o_m.ele[10] = -1 * static_cast<T>((i_far + i_near) / range);
		o_m.ele[11] = -1.0;
		o_m.ele[14] = -1 * static_cast<T>(2 * (i_near * i_far) / range);

		o_m.ele[15] = 0;

		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Orthographic(T i_left, T i_right, T i_bottom, T i_top, T i_near, T i_far)
	{
		Matrix4 o_m;
		o_m.ele[0]  = static_cast<T>(2) / (i_right - i_left);
		o_m.ele[5]  = static_cast<T>(2) / (i_top - i_bottom);
		o_m.ele[10] = -static_cast<T>(2) / (i_far - i_near);
		o_m.ele[3]  = -(i_right + i_left) / (i_right - i_left);
		o_m.ele[7]  = -(i_top + i_bottom) / (i_top - i_bottom);
		o_m.ele[11] = -(i_far + i_near) / (i_far - i_near);
		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Transpose(Matrix4<T> i_m)
	{
		Matrix4 o_m;
		o_m = i_m;
		o_m.Transpose();
		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Inverse(Matrix4<T> i_m)
	{
		Matrix4 o_m;
		o_m = i_m;
		o_m.Inverse();
		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Translate(Vec3<T> i_v)
	{
		Matrix4 o_m;
		o_m.ele[12] = i_v.x; o_m.ele[13] = i_v.y; o_m.ele[14] = i_v.z; o_m.ele[15] = static_cast<T>(1);
		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::EulerAngleZYX(T x, T y, T z)
	{
		Matrix4 o_m;

		T c1 = cosf(x);
		T s1 = sinf(x);
		T c2 = cosf(y);
		T s2 = sinf(y);
		T c3 = cosf(z);
		T s3 = sinf(z);

		o_m.ele[0] = c1 * c2;
		o_m.ele[1] = c2 * s1;
		o_m.ele[2] = -s2;
		o_m.ele[3] = static_cast<T>(0);
		o_m.ele[4] = c1 * s2 * s3 - c3 * s1;
		o_m.ele[5] = c1 * c3 + s1 * s2 * s3;
		o_m.ele[6] = c2 * s3;
		o_m.ele[7] = static_cast<T>(0);
		o_m.ele[8] = s1 * s3 + c1 * c3 * s2;
		o_m.ele[9] = c3 * s1 * s2 - c1 * s3;
		o_m.ele[10] = c2 * c3;
		o_m.ele[11] = static_cast<T>(0);
		o_m.ele[12] = static_cast<T>(0);
		o_m.ele[13] = static_cast<T>(0);
		o_m.ele[14] = static_cast<T>(0);
		o_m.ele[15] = static_cast<T>(1);

		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::Scale(Vec3<T> i_v)
	{
		Matrix4 o_m;
		o_m.ele[0] = i_v.x; o_m.ele[5] = i_v.y; o_m.ele[10] = i_v.z;
		return o_m;
	}

	template<typename T>
	inline Matrix4<T> Matrix4<T>::TruncateToMat3(Matrix4<T> i_m)
	{
		Matrix4 o_m;
		o_m = i_m;
		o_m.ele[3] = 0;
		o_m.ele[7] = 0;
		o_m.ele[11] = 0;
		o_m.ele[12] = 0;
		o_m.ele[13] = 0;
		o_m.ele[14] = 0;
		o_m.ele[15] = static_cast<T>(1.0);
		return o_m;
	}

	//template<typename T>
	//inline T Matrix4<T>::Determinant(Matrix4<T> i_m)
	//{

	//}

	//template<typename T>
	//inline bool Matrix4<T>::Decompose(Matrix4<T> i_matrix, Vec3<T>& o_scale, Quaternion<T>& o_orientation, Vec3<T>& o_translation)
	//{
	//	Matrix4<T> local = i_matrix;
	//	o_translation = static_cast<Vec3<T>>(i_matrix.column[3]);

	//	local.column[3][0] = 0;
	//	local.column[3][1] = 0;
	//	local.column[3][2] = 0;
	//}

	template<typename T>
	inline bool Matrix4<T>::Decompose(Matrix4<T> i_matrix, Vec3<T>& o_scale, Quaternion<T>& o_orientation, Vec3<T>& o_translation, Vec3<T>& o_skew, Vec4<T>& o_perspective)
	{
		Matrix4<T> local_matrix(i_matrix);
		if (EpsilonEqual(local_matrix[3][3], static_cast<T>(0), (float)1.0e-10))
			return false;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				local_matrix[i][j] /= local_matrix[3][3];

		Matrix4<T> perspective_matrix(local_matrix);

		for (int i = 0; i < 3; i++)
			perspective_matrix[i][3] = static_cast<T>(0);
		perspective_matrix[3][3] = static_cast<T>(1);

		//if(!EpsilonEqual(Matrix4<T>::Determinant(perspective_matrix), static_cast<T>(0), std::numeric_limits<T>::epsilon<T>()))
		//	return false;

		if (EpsilonNotEqual(local_matrix[0][3], static_cast<T>(0), (float)1.0e-10) ||
			EpsilonNotEqual(local_matrix[1][3], static_cast<T>(0), (float)1.0e-10) ||
			EpsilonNotEqual(local_matrix[2][3], static_cast<T>(0), (float)1.0e-10))
		{
			Vec4<T> right_hand_side;
			right_hand_side.x = local_matrix[0][3];
			right_hand_side.y = local_matrix[1][3];
			right_hand_side.z = local_matrix[2][3];
			right_hand_side.w = local_matrix[3][3];

			Matrix4<T> inversed_perspective_matrix = Inverse(perspective_matrix);
			Matrix4<T> transposed_inversed_perspective_matrix = Transpose(inversed_perspective_matrix);

			o_perspective = transposed_inversed_perspective_matrix * right_hand_side;

			local_matrix[0][3] = local_matrix[1][3] = local_matrix[2][3] = static_cast<T>(0);
			local_matrix[3][3] = static_cast<T>(1);
		}
		else
		{
			o_perspective = Vec4<T>(0, 0, 0, 1);
		}

		o_translation = Vec3<T>(local_matrix[3]);
		local_matrix[3] = Vec4<T>(0, 0, 0, local_matrix[3].w);

		Vec3<T> row[3], pdum3;

		// Now get scale and shear.
		for (int i = 0; i < 3; ++i){ 
			for (int j = 0; j < 3; ++j)
			{
				row[i][j] = local_matrix[i][j];				
			}
		}

		// Compute X scale factor and normalize first row.
		o_scale.x = row[0].Length();

		row[0].Normalize();

		// Compute XY shear factor and make 2nd row orthogonal to 1st.
		o_skew.z = row[0].Dot(row[1]);
		row[1] = static_cast<T>(1) * row[1] - o_skew.z * row[0];

		// Now, compute Y scale and normalize 2nd row.
		o_scale.y = row[1].Length();
		row[1].Normalize();
		o_skew.z /= o_scale.y;

		// Compute XZ and YZ shears, orthogonalize 3rd row.
		o_skew.y = row[0].Dot(row[2]);
		row[2] = static_cast<T>(1) * row[2] - o_skew.y * row[0];
		o_skew.x = row[1].Dot(row[2]);
		row[2] = static_cast<T>(1) * row[2] - o_skew.x * row[1];

		// Next, get Z scale and normalize 3rd row.
		o_scale.z = row[2].Length();
		row[2].Normalize();
		o_skew.y /= o_scale.z;
		o_skew.x /= o_scale.z;
		
		pdum3 = row[1].Cross(row[2]); 
		if (row[0].Dot(pdum3) < 0)
		{
			for (int i = 0; i < 3; i++)
			{
				o_scale[i] *= static_cast<T>(-1);
				row[i]     *= static_cast<T>(-1);
			}
		}

		int i, j, k = 0;
		T root; 
		T trace = row[0].x + row[1].y + row[2].z;
		if (trace > static_cast<T>(0))
		{
			root = sqrt(trace + static_cast<T>(1.0));
			o_orientation.w = static_cast<T>(0.5) * root;
			root = static_cast<T>(0.5) / root;
			o_orientation.x = root * (row[1].z - row[2].y);
			o_orientation.y = root * (row[2].x - row[0].z);
			o_orientation.z = root * (row[0].y - row[1].x);
		} // End if > 0
		else
		{
			static int next[3] = { 1, 2, 0 };
			i = 0;
			if (row[1].y > row[0].x) i = 1;
			if (row[2].z > row[i][i]) i = 2;
			j = next[i];
			k = next[j];

			root = sqrt(row[i][i] - row[j][j] - row[k][k] + static_cast<T>(1.0));			
			o_orientation[i] = static_cast<T>(0.5) * root;
			root = static_cast<T>(0.5) / root;
			o_orientation[j] = root * (row[i][j] + row[j][i]);
			o_orientation[k] = root * (row[i][k] + row[k][i]);
			o_orientation.w = root * (row[j][k] - row[k][j]);			
		} // End if <= 0

		return true;
	}
}