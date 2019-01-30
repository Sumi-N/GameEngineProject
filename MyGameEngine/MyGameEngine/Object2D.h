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

	virtual void show() const;
	void randomName(int);
	void setPosition(const double,const double);
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

inline void Object2D::show() const
{
	printf("%s is at (%f,%f)\n", name.String(), pos.x, pos.y);
}

inline void Object2D::setPosition(const double i_x, const double i_y) {
	pos.x = i_x;
	pos.y = i_y;
}
