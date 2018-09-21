#include "Monster.h"
#include <iostream>



Monster::Monster()
{
	Object2D::randomName(5);
}


Monster::~Monster()
{
}

Monster::Monster(int x, int y) {
	pos.setX(x);
	pos.setY(y);
}

void Monster::setPositions() {
	this->pos.setX(rand() % 3);
	this->pos.setY(rand() % 3);
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
