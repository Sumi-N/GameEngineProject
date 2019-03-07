#pragma once
#include "Vector4D.h"

#include <assert.h>

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
	Matrix4(float[]);
	Matrix4(Vector4D[]);
	Matrix4(const Matrix4 &);
	Matrix4();

	Vector4D operator*(const Vector4D);
	Matrix4 operator*(const Matrix4);

	void tranpose();
	void inversion();
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

inline Matrix4::Matrix4(float i_floats[]) {
	if (sizeof(i_floats)/sizeof(*i_floats) != 16) {
		assert(0);
	}
	for (int i = 0; i < 16; i++) {
		ele[i] = i_floats[i];
	}
	for (int i = 0; i < 4; i++) {
		row[i] = Row(ele[i * 4], ele[i * 4 + 1], ele[i * 4 + 2], ele[i * 4 +3]);
		col[i] = Collumn(ele[i], ele[i + 4], ele[i + 8], ele[i + 12]);
	}
}