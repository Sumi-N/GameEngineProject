#pragma once
#include <stdio.h>
template <class T, class U> class Vector2D
{
public:
	Vector2D();
	Vector2D(T, U);
	~Vector2D();
	
	Vector2D<T,U> & operator+(const Vector2D);
	Vector2D<T,U> & operator-(const Vector2D);
	bool operator==(const Vector2D) const;
	bool operator!=(const Vector2D) const;
	Vector2D<T, U> & operator=(const Vector2D &);

	T x() const { return data1; };
	U y() const { return data2; };
	Vector2D get() const { return this; }

	void setX(T _data1) { data1 = _data1; }
	void setY(U _data2) { data2 = _data2; }
	void set(Vector2D vec) { data1 = vec.data1; data2 = vec.data2; }

private:
	T data1;
	U data2;
};

template <class T, class U> Vector2D<T, U>::Vector2D() {

}

template <class T, class U> Vector2D<T,U>::Vector2D(T _data1, U _data2) {
	data1 = _data1;
	data2 = _data2;
}

template <class T, class U> Vector2D<T, U>::~Vector2D() {
	//printf("destractor of Vector2D is called \n");
}

template <class T, class U> Vector2D<T,U> & Vector2D<T, U>::operator+(const Vector2D vec){
	data1 += vec.data1;
	data2 += vec.data2;
	return *this;
}

template <class T, class U> Vector2D<T,U> & Vector2D<T, U>::operator-(const Vector2D vec){
	data1 -= vec.data1;
	data2 -= vec.data2;
	return *this;
}

template <class T, class U>  bool Vector2D<T, U>::operator==(const Vector2D vec) const{
	if (data1 == vec.data1 && data2 == vec.data2) {
		return true;
	}
	else {
		return false;
	}
}

template <class T, class U>  bool Vector2D<T, U>::operator!=(const Vector2D vec) const{
	return !(this == (vec));
}

template <class T, class U>  Vector2D<T,U> & Vector2D<T, U>::operator=(const Vector2D<T,U> & vec) {
	this->data1 = vec.data1;
	this->data2 = vec.data2;
	return *this;
}

