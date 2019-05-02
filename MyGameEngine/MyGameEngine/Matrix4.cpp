#pragma once
#include "Matrix4.h"

#include <intrin.h>

void Matrix4::inversion()
{
	float absoluteValue = ele[0] * (ele[5] * ele[10] * ele[15] + ele[6] * ele[11] * ele[13] + ele[7] * ele[9] * ele[14] - ele[7] * ele[10] * ele[13] - ele[6] * ele[9] * ele[15] - ele[5] * ele[11] * ele[14])
		- ele[4] * (ele[1] * ele[10] * ele[15] + ele[2] * ele[11] * ele[13] + ele[3] * ele[9] * ele[14] - ele[3] * ele[10] * ele[13] - ele[2] * ele[9] * ele[15] - ele[1] * ele[11] * ele[14])
		+ ele[8] * (ele[1] * ele[6] * ele[15] + ele[2] * ele[7] * ele[13] + ele[3] * ele[5] * ele[14] - ele[3] * ele[6] * ele[13] - ele[2] * ele[5] * ele[15] - ele[1] * ele[7] * ele[14]) +
		-ele[12] * (ele[1] * ele[6] * ele[11] + ele[2] * ele[7] * ele[9] + ele[3] * ele[5] * ele[10] - ele[3] * ele[6] * ele[9] - ele[2] * ele[5] * ele[11] - ele[1] * ele[7] * ele[10]);

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
		tmp.ele[i] = tmp.ele[i] / absoluteValue;
	}

	*this = tmp;

	return;
}

void Matrix4::inverseSSE(Matrix4 & o_out) const
{
	__m128 temp = { 0.0f };
	__m128 row0, row1, row2, row3;
	__m128 minor0, minor1, minor2, minor3;

	temp = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_11)), reinterpret_cast<const __m64 *>(&m_21));
	row1 = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_31)), reinterpret_cast<const __m64 *>(&m_41));
	row0 = _mm_shuffle_ps(temp, row1, 0x88);
	row1 = _mm_shuffle_ps(row1, temp, 0xDD);
	temp = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_13)), reinterpret_cast<const __m64 *>(&m_23));
	row3 = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_33)), reinterpret_cast<const __m64 *>(&m_43));
	row2 = _mm_shuffle_ps(temp, row3, 0x88);
	row3 = _mm_shuffle_ps(row3, temp, 0xDD);

	// -----------------------------------------------
	temp = _mm_mul_ps(row2, row3);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor0 = _mm_mul_ps(row1, temp);
	minor1 = _mm_mul_ps(row0, temp);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor0 = _mm_sub_ps(_mm_mul_ps(row1, temp), minor0);
	minor1 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor1);
	minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);

	// -----------------------------------------------
	temp = _mm_mul_ps(row1, row2);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor0 = _mm_add_ps(_mm_mul_ps(row3, temp), minor0);
	minor3 = _mm_mul_ps(row0, temp);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, temp));
	minor3 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor3);
	minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

	// -----------------------------------------------
	temp = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	row2 = _mm_shuffle_ps(row2, row2, 0x4E);
	minor0 = _mm_add_ps(_mm_mul_ps(row2, temp), minor0);
	minor2 = _mm_mul_ps(row0, temp);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, temp));
	minor2 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor2);
	minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

	// -----------------------------------------------
	temp = _mm_mul_ps(row0, row1);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor2 = _mm_add_ps(_mm_mul_ps(row3, temp), minor2);
	minor3 = _mm_sub_ps(_mm_mul_ps(row2, temp), minor3);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor2 = _mm_sub_ps(_mm_mul_ps(row3, temp), minor2);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, temp));

	// -----------------------------------------------
	temp = _mm_mul_ps(row0, row3);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, temp));
	minor2 = _mm_add_ps(_mm_mul_ps(row1, temp), minor2);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor1 = _mm_add_ps(_mm_mul_ps(row2, temp), minor1);
	minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, temp));

	// -----------------------------------------------
	temp = _mm_mul_ps(row0, row2);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor1 = _mm_add_ps(_mm_mul_ps(row3, temp), minor1);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, temp));
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, temp));
	minor3 = _mm_add_ps(_mm_mul_ps(row1, temp), minor3);

	// -----------------------------------------------
	__m128 det;

	det = _mm_mul_ps(row0, minor0);
	det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
	det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
	temp = _mm_rcp_ss(det);
	det = _mm_sub_ss(_mm_add_ss(temp, temp), _mm_mul_ss(det, _mm_mul_ss(temp, temp)));
	det = _mm_shuffle_ps(det, det, 0x00);

	minor0 = _mm_mul_ps(det, minor0);
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_11), minor0);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_13), minor0);

	minor1 = _mm_mul_ps(det, minor1);
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_21), minor1);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_23), minor1);

	minor2 = _mm_mul_ps(det, minor2);
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_31), minor2);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_33), minor2);

	minor3 = _mm_mul_ps(det, minor3);
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_41), minor3);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_43), minor3);

}

void Matrix4::multiplySSE(const Matrix4 & i_other, Matrix4 & o_out) const
{
	// load i_other
	__m128 rhs_row1 = _mm_load_ps(&i_other.m_11);
	__m128 rhs_row2 = _mm_load_ps(&i_other.m_21);
	__m128 rhs_row3 = _mm_load_ps(&i_other.m_31);
	__m128 rhs_row4 = _mm_load_ps(&i_other.m_41);

	__m128 acc;

	// (*this).col1 * i_other
	// m_11 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_11), rhs_row1);
	// m_12 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_12), rhs_row2));
	// m_13 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_13), rhs_row3));
	// m_14 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_14), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_11), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_13), acc);

	// (*this).col2 * i_other
	// m_21 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_21), rhs_row1);
	// m_22 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_22), rhs_row2));
	// m_23 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_23), rhs_row3));
	// m_24 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_24), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_21), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_23), acc);

	// (*this).col3 * i_other
	// m_31 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_31), rhs_row1);
	// m_32 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_32), rhs_row2));
	// m_33 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_33), rhs_row3));
	// m_34 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_34), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_31), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_33), acc);

	// (*this).col4 * i_other
	// m_41 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_41), rhs_row1);
	// m_42 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_42), rhs_row2));
	// m_43 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_43), rhs_row3));
	// m_44 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_44), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_41), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_43), acc);

}