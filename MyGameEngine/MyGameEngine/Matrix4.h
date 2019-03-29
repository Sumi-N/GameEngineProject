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

	Vector4D operator*(const Vector4D) const;
	Vector3D operator*(const Vector3D) const;
	Matrix4 operator*(const Matrix4) const;
	friend Matrix4 operator*(const float, const Matrix4 &);
	friend Matrix4 operator/(const Matrix4 &, const float);
	Matrix4 operator+(const Matrix4) const;
	Matrix4 operator-(const Matrix4) const;

	void tranpose();
	void inversion();
	void show();

	static Matrix4 Translation(float, float, float);
	static Matrix4 Roll(float);
	static Matrix4 Pitch(float);
	static Matrix4 Yaw(float);
	static Matrix4 Scaling(float);
	static Matrix4 Roataion(float, float, float);

private:
	float ele[16];
	Row   row[4];
	Collumn col[4];

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
	for (int i = 0; i < 4; i++) {
		row[i] = Row(0, 0, 0, 0);
		col[i] = Collumn(0, 0, 0, 0);
	}
}

inline Matrix4::Matrix4(float i_floats[16]) {
	for (int i = 0; i < 16; i++) {
		ele[i] = i_floats[i];
	}
	for (int i = 0; i < 4; i++) {
		row[i] = Row(ele[i * 4], ele[i * 4 + 1], ele[i * 4 + 2], ele[i * 4 +3]);
		col[i] = Collumn(ele[i], ele[i + 4], ele[i + 8], ele[i + 12]) ;
	}
}

inline Matrix4::Matrix4(const Matrix4 & i_matrix4)
{
	for (int i = 0; i < 16 ; i++) {
		ele[i] = i_matrix4.ele[i];
	}
	for (int i = 0; i < 4; i++) {
		row[i] = i_matrix4.row[i];
		col[i] = i_matrix4.col[i];
	}
}

inline Vector4D Matrix4::operator*(const Vector4D i_vector) const
{
	Vector4D o_vector;
	o_vector.x = ele[0] * i_vector.x + ele[1] * i_vector.y + ele[2] * i_vector.z + ele[3] * i_vector.w;
	o_vector.y = ele[4] * i_vector.x + ele[5] * i_vector.y + ele[6] * i_vector.z + ele[7] * i_vector.w;
	o_vector.z = ele[8] * i_vector.x + ele[9] * i_vector.y + ele[10] * i_vector.z + ele[11] * i_vector.w;
	o_vector.w = ele[12] * i_vector.x + ele[13] * i_vector.y + ele[14] * i_vector.z + ele[15] * i_vector.w;
	return o_vector;
}

inline Vector3D Matrix4::operator*(const Vector3D i_vector) const
{
	Vector4D tmp_vec4d = Vector4D(i_vector.x, i_vector.y, i_vector.z, 1);
	tmp_vec4d = (*this) * tmp_vec4d;
	Vector3D o_vec = Vector3D(tmp_vec4d.x, tmp_vec4d.y, tmp_vec4d.z);
	return o_vec;
}

inline Matrix4 Matrix4::operator*(const Matrix4 i_matrix) const
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

	for (int i = 0; i < 4; i++) {
		o_matrix.row[i] = Row(o_matrix.ele[i * 4], o_matrix.ele[i * 4 + 1], o_matrix.ele[i * 4 + 2], o_matrix.ele[i * 4 + 3]);
		o_matrix.col[i] = Collumn(o_matrix.ele[i], o_matrix.ele[i + 4], o_matrix.ele[i + 8], o_matrix.ele[i + 12]);
	}

	return o_matrix;
}

inline Matrix4 operator*(const float i_float, const Matrix4 & i_matrix)
{
	Matrix4 o_matrix;
	for (int i = 0; i < 16; i++) {
		o_matrix.ele[i] = i_float * i_matrix.ele[i];
	}

	for (int i = 0; i < 4; i++) {
		o_matrix.row[i] = Matrix4::Row(o_matrix.ele[i * 4], o_matrix.ele[i * 4 + 1], o_matrix.ele[i * 4 + 2], o_matrix.ele[i * 4 + 3]);
		o_matrix.col[i] = Matrix4::Collumn(o_matrix.ele[i], o_matrix.ele[i + 4], o_matrix.ele[i + 8], o_matrix.ele[i + 12]);
	}
	return o_matrix;
}

inline Matrix4 operator/(const Matrix4 & i_matrix, const float i_float)
{
	Matrix4 o_matrix;
	for (int i = 0; i < 16; i++) {
		o_matrix.ele[i] = i_matrix.ele[i] / i_float; 
	}

	for (int i = 0; i < 4; i++) {
		o_matrix.row[i] = Matrix4::Row(o_matrix.ele[i * 4], o_matrix.ele[i * 4 + 1], o_matrix.ele[i * 4 + 2], o_matrix.ele[i * 4 + 3]);
		o_matrix.col[i] = Matrix4::Collumn(o_matrix.ele[i], o_matrix.ele[i + 4], o_matrix.ele[i + 8], o_matrix.ele[i + 12]);
	}
	return o_matrix;
}

inline Matrix4 Matrix4::operator+(const Matrix4 i_matrix) const
{
	Matrix4 o_matrix;
	for (int i = 0; i < 16; i++) {
		o_matrix.ele[i] = this->ele[i] + i_matrix.ele[i];
	}

	for (int i = 0; i < 4; i++) {
		o_matrix.row[i] = Row(o_matrix.ele[i * 4], o_matrix.ele[i * 4 + 1], o_matrix.ele[i * 4 + 2], o_matrix.ele[i * 4 + 3]);
		o_matrix.col[i] = Collumn(o_matrix.ele[i], o_matrix.ele[i + 4], o_matrix.ele[i + 8], o_matrix.ele[i + 12]);
	}

	return o_matrix;
}

inline Matrix4 Matrix4::operator-(const Matrix4 i_matrix) const
{
	Matrix4 o_matrix;
	for (int i = 0; i < 16; i++) {
		o_matrix.ele[i] = this->ele[i] - i_matrix.ele[i];
	}

	for (int i = 0; i < 4; i++) {
		o_matrix.row[i] = Row(o_matrix.ele[i * 4], o_matrix.ele[i * 4 + 1], o_matrix.ele[i * 4 + 2], o_matrix.ele[i * 4 + 3]);
		o_matrix.col[i] = Collumn(o_matrix.ele[i], o_matrix.ele[i + 4], o_matrix.ele[i + 8], o_matrix.ele[i + 12]);
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

	for (int i = 0; i < 4; i++) {
		row[i] = Row(ele[i * 4], ele[i * 4 + 1], ele[i * 4 + 2], ele[i * 4 + 3]);
		col[i] = Collumn(ele[i], ele[i + 4], ele[i + 8], ele[i + 12]);
	}
}

inline void Matrix4::inversion()
{
	float absoluteValue = ele[0] * ( ele[5] * ele[10] * ele[15] + ele[6] * ele[11] * ele[13] + ele[7] * ele[9] * ele[14] - ele[7] * ele[10] * ele[13] - ele[6] * ele[9] * ele[15] - ele[5] * ele[11] * ele[14])
						  - ele[4] * ( ele[1] * ele[10] * ele[15] + ele[2] * ele[11] * ele[13] + ele[3] * ele[9] * ele[14] - ele[3] * ele[10] * ele[13] - ele[2] * ele[9] * ele[15] - ele[1] * ele[11] * ele[14])
						  + ele[8] * ( ele[1] * ele[6] * ele[15] + ele[2] * ele[7] * ele[13] + ele[3] * ele[5] * ele[14] - ele[3] * ele[6] * ele[13] - ele[2] * ele[5] * ele[15] - ele[1] * ele[7] * ele[14]) +
						  - ele[12] * ( ele[1] * ele[6] * ele[11] + ele[2] * ele[7] * ele[9] + ele[3] * ele[5] * ele[10] - ele[3] * ele[6] * ele[9] - ele[2] * ele[5] * ele[11] - ele[1] * ele[7] * ele[10]);

	assert(absoluteValue != 0);

	Matrix4 tmp;

	tmp.ele[0] = ele[5] * ele[10] * ele[15] + ele[6] * ele[11] * ele[13] + ele[7] * ele[9] * ele[14] - ele[7] * ele[10] * ele[13] - ele[6] * ele[9] * ele[15] - ele[5] * ele[11] * ele[14];
	tmp.ele[1] = ele[4] * ele[10] * ele[15] + ele[6] * ele[11] * ele[12] + ele[7] * ele[8] * ele[14] - ele[7] * ele[10] * ele[12] - ele[6] * ele[8] * ele[15] - ele[4] * ele[11] * ele[14];
	tmp.ele[2] = ele[4] * ele[9] * ele[15] + ele[5] * ele[11] * ele[12] + ele[7] * ele[8] * ele[13] - ele[7] * ele[9] * ele[12] - ele[5] * ele[8] * ele[15] - ele[4] * ele[11] * ele[13];
	tmp.ele[3] = ele[4] * ele[9] * ele[14] + ele[5] * ele[10] * ele[12] + ele[6] * ele[8] * ele[13] - ele[6] * ele[9] * ele[12] - ele[5] * ele[8] * ele[14] - ele[4] * ele[10] * ele[13];

	tmp.ele[4] = ele[1] * ele[10] * ele[15] + ele[2] * ele[11] * ele[13] + ele[3] * ele[9] * ele[14] - ele[3] * ele[10] * ele[13] - ele[2] * ele[9] * ele[15] - ele[1] * ele[11] * ele[14];
	tmp.ele[5] = ele[0] * ele[10] * ele[15] + ele[2] * ele[11] * ele[12] + ele[3] * ele[8] * ele[14] - ele[3] * ele[10] * ele[12] - ele[2] * ele[8] * ele[15] - ele[0] * ele[11] * ele[14];
	tmp.ele[6] = ele[0] * ele[9] * ele[15] + ele[1] * ele[11] * ele[12] + ele[3] * ele[8] * ele[13] - ele[3] * ele[9] * ele[12] - ele[1] * ele[8] * ele[15] - ele[0] * ele[11] * ele[13];
	tmp.ele[7] = ele[0] * ele[9] * ele[14] + ele[1] * ele[10] * ele[12] + ele[2] * ele[8] * ele[13] - ele[2] * ele[9] * ele[12] - ele[1] * ele[8] * ele[14] - ele[0] * ele[10] * ele[13];

	tmp.ele[8] = ele[1] * ele[6] * ele[15] + ele[2] * ele[7] * ele[13] + ele[3] * ele[5] * ele[14] - ele[3] * ele[6] * ele[13] - ele[2] * ele[5] * ele[15] - ele[1] * ele[7] * ele[14];
	tmp.ele[9] = ele[0] * ele[6] * ele[15] + ele[2] * ele[7] * ele[12] + ele[3] * ele[4] * ele[14] - ele[3] * ele[6] * ele[12] - ele[2] * ele[4] * ele[15] - ele[0] * ele[7] * ele[14];
	tmp.ele[10] = ele[0] * ele[5] * ele[15] + ele[1] * ele[7] * ele[12] + ele[3] * ele[4] * ele[13] - ele[3] * ele[5] * ele[12] - ele[1] * ele[4] * ele[15] - ele[0] * ele[7] * ele[13];
	tmp.ele[11] = ele[0] * ele[5] * ele[14] + ele[1] * ele[6] * ele[12] + ele[2] * ele[4] * ele[13] - ele[2] * ele[5] * ele[12] - ele[1] * ele[4] * ele[14] - ele[0] * ele[6] * ele[13];

	tmp.ele[12] = ele[1] * ele[6] * ele[11] + ele[2] * ele[7] * ele[9] + ele[3] * ele[5] * ele[10] - ele[3] * ele[6] * ele[9] - ele[2] * ele[5] * ele[11] - ele[1] * ele[7] * ele[10];
	tmp.ele[13] = ele[0] * ele[6] * ele[11] + ele[2] * ele[7] * ele[8] + ele[3] * ele[4] * ele[10] - ele[3] * ele[6] * ele[8] - ele[2] * ele[4] * ele[11] - ele[0] * ele[7] * ele[10];
	tmp.ele[14] = ele[0] * ele[5] * ele[11] + ele[1] * ele[7] * ele[8] + ele[3] * ele[4] * ele[9] - ele[3] * ele[5] * ele[8] - ele[1] * ele[4] * ele[11] - ele[0] * ele[7] * ele[9];
	tmp.ele[15] = ele[0] * ele[5] * ele[10] + ele[1] * ele[6] * ele[8] + ele[2] * ele[4] * ele[9] - ele[2] * ele[5] * ele[8] - ele[1] * ele[4] * ele[10] - ele[0] * ele[6] * ele[9];

	tmp.ele[1] = -1 * tmp.ele[1];
	tmp.ele[3] = -1 * tmp.ele[3];
	tmp.ele[4] = -1 * tmp.ele[4];
	tmp.ele[6] = -1 * tmp.ele[6];
	tmp.ele[9] = -1 * tmp.ele[9];
	tmp.ele[11] = -1 * tmp.ele[11];
	tmp.ele[12] = -1 * tmp.ele[12];
	tmp.ele[14] = -1 * tmp.ele[14];

	tmp.tranpose();

	for (int i = 0; i < 16; i++) {
		tmp.ele[i] =  tmp.ele[i] / absoluteValue;
	}

	*this = tmp;

	for (int i = 0; i < 4; i++) {
		row[i] = Row(ele[i * 4], ele[i * 4 + 1], ele[i * 4 + 2], ele[i * 4 + 3]);
		col[i] = Collumn(ele[i], ele[i + 4], ele[i + 8], ele[i + 12]);
	}

	return;
}

inline void Matrix4::show() {
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

	for (int i = 0; i < 4; i++) {
		o_matrix.row[i] = Row(o_matrix.ele[i * 4], o_matrix.ele[i * 4 + 1], o_matrix.ele[i * 4 + 2], o_matrix.ele[i * 4 + 3]);
		o_matrix.col[i] = Collumn(o_matrix.ele[i], o_matrix.ele[i + 4], o_matrix.ele[i + 8], o_matrix.ele[i + 12]);
	}

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

	for (int i = 0; i < 4; i++) {
		o_matrix.row[i] = Row(o_matrix.ele[i * 4], o_matrix.ele[i * 4 + 1], o_matrix.ele[i * 4 + 2], o_matrix.ele[i * 4 + 3]);
		o_matrix.col[i] = Collumn(o_matrix.ele[i], o_matrix.ele[i + 4], o_matrix.ele[i + 8], o_matrix.ele[i + 12]);
	}

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

	for (int i = 0; i < 4; i++) {
		o_matrix.row[i] = Row(o_matrix.ele[i * 4], o_matrix.ele[i * 4 + 1], o_matrix.ele[i * 4 + 2], o_matrix.ele[i * 4 + 3]);
		o_matrix.col[i] = Collumn(o_matrix.ele[i], o_matrix.ele[i + 4], o_matrix.ele[i + 8], o_matrix.ele[i + 12]);
	}

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

	for (int i = 0; i < 4; i++) {
		o_matrix.row[i] = Row(o_matrix.ele[i * 4], o_matrix.ele[i * 4 + 1], o_matrix.ele[i * 4 + 2], o_matrix.ele[i * 4 + 3]);
		o_matrix.col[i] = Collumn(o_matrix.ele[i], o_matrix.ele[i + 4], o_matrix.ele[i + 8], o_matrix.ele[i + 12]);
	}

	return o_matrix;
}

inline Matrix4 Matrix4::Scaling(float i_float)
{
	Matrix4 o_matrix;
	o_matrix.ele[0] = i_float;
	o_matrix.ele[5] = i_float;
	o_matrix.ele[10] = i_float;
	o_matrix.ele[15] = 1;

	for (int i = 0; i < 4; i++) {
		o_matrix.row[i] = Row(o_matrix.ele[i * 4], o_matrix.ele[i * 4 + 1], o_matrix.ele[i * 4 + 2], o_matrix.ele[i * 4 + 3]);
		o_matrix.col[i] = Collumn(o_matrix.ele[i], o_matrix.ele[i + 4], o_matrix.ele[i + 8], o_matrix.ele[i + 12]);
	}

	return o_matrix;
}
