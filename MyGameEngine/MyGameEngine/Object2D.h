#pragma once
#include "Vector2D.h"

class Object2D
{
public:
	//List<char> name;
	char *headofname;
	char *name;
	Vector2D<int, int> pos;
	Object2D();
	~Object2D();

	void showPosition();
	virtual void showName();

	void randomName(int);
private:
	int namelength;
};

