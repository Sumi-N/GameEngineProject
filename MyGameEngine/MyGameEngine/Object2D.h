#pragma once
#include "Vector2D.h"
#include "CharacterString.h"

class Object2D
{
public:
	CharacterString name;
	Vector2D<int, int> pos;
	//Vector2D<double, double> position;

	Object2D();
	~Object2D();

	virtual void showPosition();
	virtual void showName();
	virtual Vector2D<int, int> getPosition();
	virtual void setPosition(Vector2D<int, int> pos);
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

inline void Object2D::showPosition() {
	printf("%s", name.String());
	printf(" is at (%d,%d)\n", pos.x, pos.y);
}

inline void Object2D::showName() {
	printf("%s", name.String());
	printf("\n");
}

inline Vector2D<int, int> Object2D::getPosition()
{
	return pos;
}

inline void Object2D::setPosition(Vector2D<int, int> pos)
{
	this->pos = pos;
	return;
}