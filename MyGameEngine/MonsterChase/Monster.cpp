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
