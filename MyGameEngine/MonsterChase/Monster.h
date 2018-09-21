#pragma once
#include "Object2D.h"
#include "Vector2D.h"

class Monster : public Object2D
{
public:
	Monster();
	~Monster();
	Monster(int, int);
	void setPositions();
	void showPosition();
	void showName();
	Vector2D<int,int> returnPos();
};

