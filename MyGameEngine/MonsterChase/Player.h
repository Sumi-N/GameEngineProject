#pragma once
#include "Object2D.h"
class Player : public Object2D
{
public:
	Player();
	~Player();
	bool move(char);
	void setPositions();
	Vector2D<int, int> returnPos();
};

