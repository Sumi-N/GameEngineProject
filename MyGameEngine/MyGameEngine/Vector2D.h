#pragma once
#include <stdio.h>
template <class T, class U> class Vector2D
{
public:
	Vector2D();
	Vector2D(T, U);
	~Vector2D();
	
	Vector2D<T,U> operator+(const Vector2D);
	Vector2D<T,U> operator-(const Vector2D);
	Vector2D<T,U> operator*(const int);
	Vector2D<T,U> operator*(const double);
	Vector2D<T,U> operator/(const int);
	Vector2D<T,U> operator/(const double);
	Vector2D<T,U> & operator=(const Vector2D &);
	bool operator==(const Vector2D) const;
	bool operator!=(const Vector2D) const;

	Vector2D get() const { return this; }
	void set(Vector2D i_vec) { x = i_vec.x; y = i_vec.y; }

public:
	T x;
	U y;
};

template <class T, class U> 
inline Vector2D<T, U>::Vector2D() {
}

template <class T, class U> 
inline Vector2D<T,U>::Vector2D(T i_data1, U i_data2) {
	x = i_data1;
	y = i_data2;
}

template <class T, class U> 
inline Vector2D<T, U>::~Vector2D() {
}

template <class T, class U> 
inline Vector2D<T,U> Vector2D<T, U>::operator+(const Vector2D i_vec){
	Vector2D<T, U> result = Vector2D<T, U>();
	result.x = this->x + i_vec.x;
	result.y = this->y + i_vec.y;
	return result;
}

template <class T, class U> 
inline Vector2D<T,U> Vector2D<T, U>::operator-(const Vector2D i_vec){
	Vector2D<T, U> result = Vector2D<T, U>();
	result.x = this->x - i_vec.x;
	result.y = this->y - i_vec.y;
	return result;
}

template<class T, class U>
inline Vector2D<T, U> Vector2D<T, U>::operator*(const int i_int)
{
	Vector2D<T, U> result = Vector2D<T, U>();
	result.x = x * i_int;
	result.y = y * i_int;
	return result;
}

template<class T, class U>
inline Vector2D<T, U> Vector2D<T, U>::operator*(const double i_double)
{
	Vector2D<T, U> result = Vector2D<T,U>();
	result.x = x * i_double;
	result.y = y * i_double;
	return result;
}

template<class T, class U>
inline Vector2D<T, U> Vector2D<T, U>::operator/(const int i_int)
{
	Vector2D<T, U> result = Vector2D<T, U>();
	result.x = x / i_int;
	result.y = y / i_int;
	return result;
}

template<class T, class U>
inline Vector2D<T, U> Vector2D<T, U>::operator/(const double i_double)
{
	Vector2D<T, U> result = Vector2D<T, U>();
	result.x = x / i_double;
	result.y = y / i_double;
	return result;
}

template <class T, class U>  
inline bool Vector2D<T, U>::operator==(const Vector2D i_vec) const{
	if (x == i_vec.x && y == i_vec.y)
		return true;
	else
		return false;
}

template <class T, class U>  
inline bool Vector2D<T, U>::operator!=(const Vector2D i_vec) const{
	return !(this == (i_vec));
}

template <class T, class U>  
inline Vector2D<T,U> & Vector2D<T, U>::operator=(const Vector2D<T,U> & i_vec) {
	this->x = i_vec.x;
	this->y = i_vec.y;
	return *this;
}