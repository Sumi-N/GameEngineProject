#pragma once

#define _USE_MATH_DEFINES

#include "Vector3D.h"
#include "Vector4D.h"
#include "DebugLog.h"

#include <assert.h>
#include <array>
#include <math.h>

class Matrix4 
{
public:
	struct Row //Horizontal
	{
		float ele[4];
		Row() {ele[0] = ele[1] = ele[2] = ele[3] = 0;};
		Row(float a, float b, float c, float d) { ele[0] = a, ele[1] = b, ele[2] = c, ele[3] = d; };
		Row(Vector4D);
	};
	struct Collumn //Vertical
	{
		float ele[4];
		Collumn() { ele[0] = ele[1] = ele[2] = ele[3] = 0; };
		Collumn(float a, float b, float c, float d) { ele[0] = a, ele[1] = b, ele[2] = c, ele[3] = d; };
		Collumn(Vector4D);
	};

	Matrix4();
	Matrix4(float[16]);
	Matrix4(Vector4D[4]);
	Matrix4(const Matrix4 &);

	Vector4D operator*(const Vector4D &) const;
	Vector3D operator*(const Vector3D &) const;
	Matrix4 operator*(const Matrix4 &) const;
	friend Matrix4 operator*(const float, const Matrix4 &);
	friend Matrix4 operator/(const Matrix4 &, const float);
	Matrix4 operator+(const Matrix4 &) const;
	Matrix4 operator-(const Matrix4 &) const;
	void tranpose();
	void inversion();
	void show() const;
	void inverseSSE(Matrix4 &) const;
	void multiplySSE(const Matrix4 &, Matrix4 &) const;

	static Matrix4 Translation(float, float, float);
	static Matrix4 Roll(float);
	static Matrix4 Pitch(float);
	static Matrix4 Yaw(float);
	static Matrix4 Scaling(float);
	static Matrix4 Roataion(float, float, float);

private:
	union {
		struct
		{
			float m_11, m_12, m_13, m_14,
				  m_21, m_22, m_23, m_24,
				  m_31, m_32, m_33, m_34,
				  m_41, m_42, m_43, m_44;
		};
		float ele[16];

		Row   row[4];
		Collumn col[4]; // This is not correct, need to be fixed later
	};

	/*
	[ 0, 1, 2, 3]
	[ 4, 5, 6, 7]
	[ 8, 9,10,11]
	[12,13,14,15]
	*/
};

inline Matrix4::Matrix4() {
	for (int i = 0; i < 16; i++) {
		ele[i] = 0;
	}
}

inline Matrix4::Matrix4(float i_floats[16]) {
	for (int i = 0; i < 16; i++) {
		ele[i] = i_floats[i];
	}
}

inline Matrix4::Matrix4(const Matrix4 & i_matrix4)
{
	for (int i = 0; i < 16 ; i++) {
		ele[i] = i_matrix4.ele[i];
	}
}

inline Vector4D Matrix4::operator*(const Vector4D & i_vector) const
{
	Vector4D o_vector;
	o_vector.x = ele[0] * i_vector.x + ele[1] * i_vector.y + ele[2] * i_vector.z + ele[3] * i_vector.w;
	o_vector.y = ele[4] * i_vector.x + ele[5] * i_vector.y + ele[6] * i_vector.z + ele[7] * i_vector.w;
	o_vector.z = ele[8] * i_vector.x + ele[9] * i_vector.y + ele[10] * i_vector.z + ele[11] * i_vector.w;
	o_vector.w = ele[12] * i_vector.x + ele[13] * i_vector.y + ele[14] * i_vector.z + ele[15] * i_vector.w;
	return o_vector;
}

inline Vector3D Matrix4::operator*(const Vector3D & i_vector) const
{
	Vector4D tmp_vec4d = Vector4D(i_vector.x, i_vector.y, i_vector.z, 1);
	tmp_vec4d = (*this) * tmp_vec4d;
	Vector3D o_vec = Vector3D(tmp_vec4d.x, tmp_vec4d.y, tmp_vec4d.z);
	return o_vec;
}

inline Matrix4 Matrix4::operator*(const Matrix4 & i_matrix) const
{
	Matrix4 o_matrix;
	o_matrix.ele[0] = ele[0] * i_matrix.ele[0] + ele[1] * i_matrix.ele[4] + ele[2] * i_matrix.ele[8] + ele[3] * i_matrix.ele[12];
	o_matrix.ele[1] = ele[0] * i_matrix.ele[1] + ele[1] * i_matrix.ele[5] + ele[2] * i_matrix.ele[9] + ele[3] * i_matrix.ele[13];
	o_matrix.ele[2] = ele[0] * i_matrix.ele[2] + ele[1] * i_matrix.ele[6] + ele[2] * i_matrix.ele[10] + ele[3] * i_matrix.ele[14];
	o_matrix.ele[3] = ele[0] * i_matrix.ele[3] + ele[1] * i_matrix.ele[7] + ele[2] * i_matrix.ele[11] + ele[3] * i_matrix.ele[15];
	o_matrix.ele[4] = ele[4] * i_matrix.ele[0] + ele[5] * i_matrix.ele[4] + ele[6] * i_matrix.ele[8] + ele[7] * i_matrix.ele[12];
	o_matrix.ele[5] = ele[4] * i_matrix.ele[1] + ele[5] * i_matrix.ele[5] + ele[6] * i_matrix.ele[9] + ele[7] * i_matrix.ele[13];
	o_matrix.ele[6] = ele[4] * i_matrix.ele[2] + ele[5] * i_matrix.ele[6] + ele[6] * i_matrix.ele[10] + ele[7] * i_matrix.ele[14];
	o_matrix.ele[7] = ele[4] * i_matrix.ele[3] + ele[5] * i_matrix.ele[7] + ele[6] * i_matrix.ele[11] + ele[7] * i_matrix.ele[15];
	o_matrix.ele[8] = ele[8] * i_matrix.ele[0] + ele[9] * i_matrix.ele[4] + ele[10] * i_matrix.ele[8] + ele[11] * i_matrix.ele[12];
	o_matrix.ele[9] = ele[8] * i_matrix.ele[1] + ele[9] * i_matrix.ele[5] + ele[10] * i_matrix.ele[9] + ele[11] * i_matrix.ele[13];
	o_matrix.ele[10] = ele[8] * i_matrix.ele[2] + ele[9] * i_matrix.ele[6] + ele[10] * i_matrix.ele[10] + ele[11] * i_matrix.ele[14];
	o_matrix.ele[11] = ele[8] * i_matrix.ele[3] + ele[9] * i_matrix.ele[7] + ele[10] * i_matrix.ele[11] + ele[11] * i_matrix.ele[15];
	o_matrix.ele[12] = ele[12] * i_matrix.ele[0] + ele[13] * i_matrix.ele[4] + ele[14] * i_matrix.ele[8] + ele[15] * i_matrix.ele[12];
	o_matrix.ele[13] = ele[12] * i_matrix.ele[1] + ele[13] * i_matrix.ele[5] + ele[14] * i_matrix.ele[9] + ele[15] * i_matrix.ele[13];
	o_matrix.ele[14] = ele[12] * i_matrix.ele[2] + ele[13] * i_matrix.ele[6] + ele[14] * i_matrix.ele[10] + ele[15] * i_matrix.ele[14];
	o_matrix.ele[15] = ele[12] * i_matrix.ele[3] + ele[13] * i_matrix.ele[7] + ele[14] * i_matrix.ele[11] + ele[15] * i_matrix.ele[15];

	return o_matrix;
}

inline Matrix4 operator*(const float i_float, const Matrix4 & i_matrix)
{
	Matrix4 o_matrix;
	for (int i = 0; i < 16; i++) {
		o_matrix.ele[i] = i_float * i_matrix.ele[i];
	}
	return o_matrix;
}

inline Matrix4 operator/(const Matrix4 & i_matrix, const float i_float)
{
	Matrix4 o_matrix;
	for (int i = 0; i < 16; i++) {
		o_matrix.ele[i] = i_matrix.ele[i] / i_float; 
	}
	return o_matrix;
}

inline Matrix4 Matrix4::operator+(const Matrix4 & i_matrix) const
{
	Matrix4 o_matrix;
	for (int i = 0; i < 16; i++) {
		o_matrix.ele[i] = this->ele[i] + i_matrix.ele[i];
	}

	return o_matrix;
}

inline Matrix4 Matrix4::operator-(const Matrix4 & i_matrix) const
{
	Matrix4 o_matrix;
	for (int i = 0; i < 16; i++) {
		o_matrix.ele[i] = this->ele[i] - i_matrix.ele[i];
	}

	return o_matrix;
}

inline void Matrix4::tranpose()
{
	float tmp = ele[4];
	ele[4] = ele[1];
	ele[1] = tmp;

	tmp = ele[2];
	ele[2] = ele[8];
	ele[8] = tmp;

	tmp = ele[3];
	ele[3] = ele[12];
	ele[12] = tmp;

	tmp = ele[6];
	ele[6] = ele[9];
	ele[9] = tmp;

	tmp = ele[7];
	ele[7] = ele[13];
	ele[13] = tmp;

	tmp = ele[14];
	ele[14] = ele[11];
	ele[11] = tmp;
}

inline void Matrix4::show() const {
	DEBUG_PRINT("{%f,%f,%f,%f,\n     %f,%f,%f,%f,\n     %f,%f,%f,%f,\n     %f,%f,%f,%f}"
		,ele[0], ele[1], ele[2], ele[3], ele[4], ele[5], ele[6], ele[7], ele[8], ele[9], ele[10], ele[11], ele[12], ele[13], ele[14], ele[15]);
}

inline Matrix4 Matrix4::Translation(float i_x, float i_y, float i_z)
{
	Matrix4 o_matrix;
	o_matrix.ele[0] = 1;
	o_matrix.ele[5] = 1;
	o_matrix.ele[10] = 1;
	o_matrix.ele[15] = 1;

	o_matrix.ele[3] = i_x;
	o_matrix.ele[7] = i_y;
	o_matrix.ele[11] = i_z;

	return o_matrix;
}

inline Matrix4 Matrix4::Roll(float i_degree)
{
	Matrix4 o_matrix;
	float radian = i_degree * 2 * static_cast<float>(M_PI) / 360;
	o_matrix.ele[5] = cosf(radian);
	o_matrix.ele[6] = -sinf(radian);
	o_matrix.ele[9] = sinf(radian);
	o_matrix.ele[10] = cosf(radian);
	o_matrix.ele[0] = 1;
	o_matrix.ele[15] = 1;

	return o_matrix;
}

inline Matrix4 Matrix4::Pitch(float i_degree)
{
	Matrix4 o_matrix;
	float radian = i_degree * 2 * static_cast<float>(M_PI) / 360;
	o_matrix.ele[0] = cosf(radian);
	o_matrix.ele[2] = sinf(radian);
	o_matrix.ele[8] = -sinf(radian);
	o_matrix.ele[10] = cosf(radian);
	o_matrix.ele[5] = 1;
	o_matrix.ele[15] = 1;

	return o_matrix;
}

inline Matrix4 Matrix4::Yaw(float i_degree)
{
	Matrix4 o_matrix;
	float radian = i_degree * 2 * static_cast<float>(M_PI) / 360;
	o_matrix.ele[0] = cosf(radian);
	o_matrix.ele[1] = -sinf(radian);
	o_matrix.ele[4] = sinf(radian);
	o_matrix.ele[5] = cosf(radian);
	o_matrix.ele[10] = 1;
	o_matrix.ele[15] = 1;

	return o_matrix;
}

inline Matrix4 Matrix4::Scaling(float i_float)
{
	Matrix4 o_matrix;
	o_matrix.ele[0] = i_float;
	o_matrix.ele[5] = i_float;
	o_matrix.ele[10] = i_float;
	o_matrix.ele[15] = 1;

	return o_matrix;
}
