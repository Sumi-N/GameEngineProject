#pragma once
#include "Vector2D.h"

class Object2D
{
public:
	//List<char> name;
	char *headofname;
	char *name;
	int namelength;
	Vector2D<int, int> pos;
	Object2D();
	~Object2D();

	virtual void showPosition();
	virtual void showDirection();
	virtual void showName();

	void randomName(int);
};

