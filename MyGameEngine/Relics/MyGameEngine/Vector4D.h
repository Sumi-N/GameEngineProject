#pragma once

class Vector4D
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4D();
	Vector4D(const Vector4D &);
	Vector4D(const float, const float, const float, const float);
	~Vector4D();

	Vector4D & operator=(const Vector4D &);
	Vector4D operator+(const Vector4D &) const;
	Vector4D operator-(const Vector4D &) const;
	Vector4D operator*(const Vector4D &) const;
	Vector4D operator*(const float &) const;
	Vector4D operator/(const Vector4D &) const;
	Vector4D operator/(const float &) const;
	bool operator==(const Vector4D &) const;
	bool operator!=(const Vector4D &) const;

	void set(float, float, float, float);
};

inline Vector4D::Vector4D()
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

inline Vector4D::Vector4D(const Vector4D & i_vec)
	: x(i_vec.x), y(i_vec.y), z(i_vec.z), w(i_vec.w) {}

inline Vector4D::Vector4D(const float i_x, const float i_y, const float i_z, const float i_w)
	: x(i_x), y(i_y), z(i_z), w(i_w){}

inline Vector4D::~Vector4D() {}

inline Vector4D & Vector4D::operator=(const Vector4D & i_vec) {
	this->x = i_vec.x;
	this->y = i_vec.y;
	this->z = i_vec.z;
	this->w = i_vec.w;

	return *this;
}

inline Vector4D Vector4D::operator+(const Vector4D & i_vec) const {
	Vector4D o_vec;
	o_vec.x = this->x + i_vec.x;
	o_vec.y = this->y + i_vec.y;
	o_vec.z = this->z + i_vec.z;
	o_vec.w = this->w + i_vec.w;
	return o_vec;
}

inline Vector4D Vector4D::operator-(const Vector4D & i_vec) const {
	Vector4D o_vec;
	o_vec.x = this->x - i_vec.x;
	o_vec.y = this->y - i_vec.y;
	o_vec.z = this->z - i_vec.z;
	o_vec.w = this->w - i_vec.w;
	return o_vec;
}

inline Vector4D Vector4D::operator*(const Vector4D &) const {

}

inline Vector4D Vector4D::operator*(const float & i_float) const
{
	Vector4D o_vec;
	o_vec.x = this->x * i_float;
	o_vec.y = this->y * i_float;
	o_vec.z = this->z * i_float;
	o_vec.w = this->w * i_float;
	return o_vec;
}

inline Vector4D Vector4D::operator/(const Vector4D &) const {

}

inline Vector4D Vector4D::operator/(const float & i_float) const {
	Vector4D o_vec;
	o_vec.x = this->x / i_float;
	o_vec.y = this->y / i_float;
	o_vec.z = this->z / i_float;
	o_vec.w = this->w / i_float;
	return o_vec;
}

inline bool Vector4D::operator==(const Vector4D & i_vec) const {
	if (this->x == i_vec.x && this->y == i_vec.y && this->z == i_vec.z && this->w == i_vec.w) {
		return true;
	}
	else
		return false;
}

inline bool Vector4D::operator!=(const Vector4D & i_vec) const {
	return !(*this == i_vec);
}

inline void Vector4D::set(float i_x, float i_y, float i_z, float i_w) {
	this->x = i_x;
	this->y = i_y;
	this->z = i_z;
	this->w = i_w;
}