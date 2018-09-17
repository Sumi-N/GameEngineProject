#pragma once
#include "Vector2D.h"
#include "List.h"

class Object2D
{
public:
	Object2D();
	~Object2D();
	Object2D(const Object2D &obj);

	List<char> name;
	Vector2D<int, int> pos;

	void showPosition();
	void showName();

	void randomName(int);

private:
};

