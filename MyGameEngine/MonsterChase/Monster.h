#pragma once
#include "Object2D.h"
#include "Vector2D.h"
#include <iostream>

class Monster : public Object2D
{
public:
	Monster() {};
	~Monster() {};
	Monster(int x, int y) {
		pos.setX(x);
		pos.setY(y);
	};
	void setPositions();
	void showPosition() override;
	void showName();
	Vector2D<int,int> returnPos();
	void move();
};

inline void Monster::setPositions() {
	this->pos.setX(rand() % 100);
	this->pos.setY(rand() % 100);
}

inline void Monster::showPosition(){
	std::cout << "this monster is at (" << this->pos.x() << "," << this->pos.y() << ")" << std::endl;
}

inline void Monster::showName() {
	Object2D::showName();
}

inline Vector2D<int, int> Monster::returnPos()
{
	return pos;
}

inline void Monster::move() {
	bool up = true, down = true, right = true, left = true;
	if (this->pos.x() == 0) {
		left = false;
	}
	else if (this->pos.x() == 100) {
		right = false;
	}
	if (this->pos.y() == 0) {
		up = false;
	}
	else if (this->pos.y() == 100) {
		down = false;
	}

	if (right && left) {
		pos.setX(rand() % 2 ? pos.x() + 1 : pos.x() - 1);
		pos = pos + Vector2D<int, int>(1, 1);
	}
	else {
		pos.setX(right ? pos.x() + 1 : pos.x() - 1);
	}

	if (up && down) {
		pos.setY(rand() % 2 ? pos.y() + 1 : pos.y() - 1);
	}
	else {
		pos.setY(up ? pos.y() + 1 : pos.y() - 1);
	}
}
