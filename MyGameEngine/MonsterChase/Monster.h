#pragma once
#include "Object2D.h"
#include "Vector2D.h"

class Monster : Object2D
{
public:
	Monster();
	~Monster();
	Monster(int, int);
	void setPositions();
	void showPosition();
	void showName();
};

