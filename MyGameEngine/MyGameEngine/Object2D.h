#pragma once
#include "Vector2D.h"

class Object2D
{
public:
	char *headofname;
	char *name;
	int namelength;
	Vector2D<int, int> pos;

	Object2D();
	~Object2D();
	Object2D(const Object2D & obj);

	Object2D & operator=(const Object2D & obj);

	virtual void showPosition();
	virtual void showName();
	virtual Vector2D<int, int> getPosition();
	virtual void setPosition(Vector2D<int, int> pos);
	void randomName(int);
};

