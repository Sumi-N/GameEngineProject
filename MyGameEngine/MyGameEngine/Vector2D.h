#pragma once
#include <stdio.h>
template <class T, class U> class Vector2D
{
public:
	Vector2D();
	Vector2D(T, U);
	~Vector2D();
	
	void operator+(Vector2D);
	void operator-(Vector2D);
	bool operator==(Vector2D);
	bool operator!=(Vector2D);

	T x() { return data1; };
	U y() { return data2; };

	void setX(T _data1) { data1 = _data1; }
	void setY(U _data2) { data2 = _data2; }
	void set(Vector2D vec) { data1 = vec.data1; data2 = vec.data2; }
	T getX() { return data1; }
	U getY() { return data2; }
	Vector2D get() { return this; }

private:
	T data1;
	U data2;
};

template <class T, class U> Vector2D<T,U>::Vector2D(T _data1, U _data2) {
	data1 = _data1;
	data2 = _data2;
}

template <class T, class U> Vector2D<T, U>::~Vector2D() {
	printf("this instance is deleted \n");
}

template <class T, class U> void Vector2D<T, U>::operator+(Vector2D vec) {
	data1 += vec.data1;
	data2 += vec.data2;
}

template <class T, class U> void Vector2D<T, U>::operator-(Vector2D vec) {
	data1 -= vec.data1;
	data2 -= vec.data2;
}

template <class T, class U>  bool Vector2D<T, U>::operator==(Vector2D vec) {
	if (data1 == vec.data1 && data2 == vec.data2) {
		return true;
	}
	else {
		return false;
	}
}

template <class T, class U>  bool Vector2D<T, U>::operator!=(Vector2D vec) {
	return !(this == (vec));
}

