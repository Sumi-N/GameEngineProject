#include "Monster.h"
#include <iostream>



Monster::Monster()
{
}


Monster::~Monster()
{
}

Monster::Monster(int x, int y) {
	pos.setX(x);
	pos.setY(y);
}

void Monster::setPositions() {
	this->pos.setX(rand() % 100);
	this->pos.setY(rand() % 100);
}

void Monster::showPosition() {
	Object2D::showPosition();
}

void Monster::showName() {
	Object2D::showName();
}

Vector2D<int,int> Monster::returnPos()
{
	return pos;
}

void Monster::move() {
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
		pos = rand() % 2 ? pos + Vector2D<int, int>(1, 0) : pos + Vector2D<int, int>(-1, 0);
	}
	else {
		pos = right ? pos + Vector2D<int, int>(1, 0) : pos + Vector2D<int, int>(-1, 0);
	}

	if (up && down) {
		pos = rand() % 2 ? pos + Vector2D<int, int>(0, 1) : pos + Vector2D<int, int>(0, -1);
	}
	else {
		pos = up ? pos + Vector2D<int, int>(0, 1) : pos + Vector2D<int, int>(0, -1);
	}
}
	 