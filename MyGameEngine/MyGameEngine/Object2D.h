#pragma once
#include "Vector2D.h"
#include "CharacterString.h"

class Object2D
{
public:
	CharacterString name;
	Vector2D<double, double> pos;

	Object2D();
	~Object2D();

	virtual void show();
	void randomName(int);
};

inline Object2D::Object2D()
{
	pos.x = rand() % 100;
	pos.y = rand() % 100;
}

inline Object2D::~Object2D()
{
}

inline void Object2D::randomName(int length) {
	name.Random(length);
}

inline void Object2D::show()
{
	printf("%s is at (%f,%f)\n", name.String(), pos.x, pos.y);
}
