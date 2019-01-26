#pragma once
#include "Object2D.h"
class Player : public Object2D
{
public:
	Player() {};
	~Player() {};
	void setName(const char*);
};

inline void Player::setName(const char * i_name)
{
	name = i_name;
}