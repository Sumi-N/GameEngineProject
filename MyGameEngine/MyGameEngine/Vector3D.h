#pragma once


class Vector3D
{
public:
	float x;
	float y;
	float z;

	Vector3D();
	Vector3D(const Vector3D &);
	~Vector3D();

	Vector3D & operator=(const Vector3D);
	Vector3D operator+(const Vector3D);
	Vector3D operator-(const Vector3D);
	Vector3D operator*(const Vector3D);
	Vector3D operator*(const float);
	Vector3D operator/(const Vector3D);
	Vector3D operator/(const float);
	bool operator==(const Vector3D) const;
	bool operator!=(const Vector3D) const;

	void set(float,float,float);
};

inline Vector3D::Vector3D() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

inline Vector3D::Vector3D(const Vector3D & i_vec) {
	this->x = i_vec.x;
	this->y = i_vec.y;
	this->z = i_vec.z;
}

inline Vector3D::~Vector3D() {

}

inline Vector3D & Vector3D::operator=(const Vector3D i_vec) {
	this->x = i_vec.x;
	this->y = i_vec.y;
	this->z = i_vec.z;

	return *this;
}

inline Vector3D Vector3D::operator+(const Vector3D i_vec) {
	Vector3D o_vec;
	o_vec.x = this->x + i_vec.x;
	o_vec.y = this->y + i_vec.y;
	o_vec.z = this->z + i_vec.z;
	return o_vec;
}

inline Vector3D Vector3D::operator-(const Vector3D i_vec) {
	Vector3D o_vec;
	o_vec.x = this->x - i_vec.x;
	o_vec.y = this->y - i_vec.y;
	o_vec.z = this->z - i_vec.z;
	return o_vec;
}

inline Vector3D Vector3D::operator*(const Vector3D) {

}

inline Vector3D Vector3D::operator*(const float i_float)
{
	Vector3D o_vec;
	o_vec.x = this->x * i_float;
	o_vec.y = this->y * i_float;
	o_vec.z = this->z * i_float;
	return o_vec;
}

inline Vector3D Vector3D::operator/(const Vector3D) {

}

inline Vector3D Vector3D::operator/(const float i_float) {
	Vector3D o_vec;
	o_vec.x = this->x / i_float;
	o_vec.y = this->y / i_float;
	o_vec.z = this->z / i_float;
	return o_vec;
}

inline bool Vector3D::operator==(const Vector3D i_vec) const {
	if (this->x == i_vec.x && this->y == i_vec.y && this->z == i_vec.z) {
		return true;
	}
	else
		return false;
}

inline bool Vector3D::operator!=(const Vector3D i_vec) const {
	return !( *this == i_vec);
}

inline void Vector3D::set(float i_x, float i_y, float i_z) {
	this->x = i_x;
	this->y = i_y;
	this->z = i_z;
}