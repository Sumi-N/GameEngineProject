#pragma once
#include "Vector2D.h"
#include "List.h"

class Object2D
{
public:
	Object2D();
	~Object2D();
	Object2D(const Object2D &obj) {}
	Object2D(int x, int y);
	List<char> name;
	Vector2D<int, int> pos;

private:
	void randomName(int);
};

