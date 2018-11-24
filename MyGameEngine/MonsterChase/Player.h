#pragma once
#include "Object2D.h"
class Player : public Object2D
{
public:
	Player() {};
	~Player() {};
	void setName(const char*, const int);
};

inline void Player::setName(const char * input, const int lengthofname)
{
	//name = input;
	//headofname = name;
	delete name;
	namelength = lengthofname;
	name = new char[lengthofname + 1];
	headofname = name;
	for (int i = 0; i <= lengthofname; i++) {
		name[i] = input[i];
	}
}