#pragma once
#include "Vector2D.h"

class Object2D
{
public:
	Object2D();
	~Object2D();

	void set(int, int);
	Vector2D get();


private:
	Vector2D vec;

};

