#pragma once
#include "Object2D.h"
class Player : public Object2D
{
public:
	Player();
	~Player();
	bool move(char);
	void setPositions();
	void setName(char*);
	void showName() override;
};

