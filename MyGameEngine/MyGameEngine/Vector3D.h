#pragma once

//#include "DebugLog.h"

#include <intrin.h>
#include <xmmintrin.h>

class Vector3D
{
public:
	union 
	{
		__m128 _m_vec;
		struct
		{
			float x, y, z;
		};
	};
	
	
	Vector3D();
	Vector3D(const Vector3D &);
	Vector3D(const float, const float, const float);
	~Vector3D();

	Vector3D & operator=(const Vector3D &);
	Vector3D operator+(const Vector3D &) const;
	Vector3D operator-(const Vector3D &) const;
	Vector3D operator*(const Vector3D &) const;
	friend Vector3D operator*(const float, const Vector3D);
	Vector3D operator/(const Vector3D &) const;
	Vector3D operator/(const float &) const;
	bool operator==(const Vector3D &) const;
	bool operator!=(const Vector3D &) const;

	void set(float,float,float);
};

inline Vector3D::Vector3D()
	: x(0.0f),y(0.0f),z(0.0f) {}

inline Vector3D::Vector3D(const Vector3D & i_vec)
	: x(i_vec.x), y(i_vec.y), z(i_vec.z) {}

inline Vector3D::Vector3D(const float i_x, const float i_y, const float i_z)
	: x(i_x), y(i_y), z(i_z) {}

inline Vector3D::~Vector3D() {}

inline Vector3D & Vector3D::operator=(const Vector3D & i_vec){
	this->x = i_vec.x;
	this->y = i_vec.y;
	this->z = i_vec.z;

	return *this;
}

inline Vector3D Vector3D::operator+(const Vector3D & i_vec) const {
	Vector3D o_vec;
	//o_vec.x = this->x + i_vec.x;
	//o_vec.y = this->y + i_vec.y;
	//o_vec.z = this->z + i_vec.z;
	o_vec._m_vec = _mm_add_ps(this->_m_vec, i_vec._m_vec);
	return o_vec;
}

inline Vector3D Vector3D::operator-(const Vector3D & i_vec) const {
	Vector3D o_vec;
	o_vec.x = this->x - i_vec.x;
	o_vec.y = this->y - i_vec.y;
	o_vec.z = this->z - i_vec.z;
	return o_vec;
}

inline Vector3D Vector3D::operator*(const Vector3D &) const {

}

inline Vector3D operator*(const float i_float, const Vector3D i_vector)
{
	Vector3D o_vec;
	o_vec.x = i_vector.x * i_float;
	o_vec.y = i_vector.y * i_float;
	o_vec.z = i_vector.z * i_float;
	return o_vec;
}

inline Vector3D Vector3D::operator/(const Vector3D & Vector3D) const {

}

inline Vector3D Vector3D::operator/(const float & i_float) const {
	Vector3D o_vec;
	o_vec.x = this->x / i_float;
	o_vec.y = this->y / i_float;
	o_vec.z = this->z / i_float;
	return o_vec;
}

inline bool Vector3D::operator==(const Vector3D & i_vec) const {
	if (this->x == i_vec.x && this->y == i_vec.y && this->z == i_vec.z) {
		return true;
	}
	else
		return false;
}

inline bool Vector3D::operator!=(const Vector3D & i_vec) const {
	return !( *this == i_vec);
}

inline void Vector3D::set(float i_x, float i_y, float i_z) {
	this->x = i_x;
	this->y = i_y;
	this->z = i_z;
}