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

void Monster::showMonster() {
	std::cout << "this monster is at (" << this->pos.x() << "," << this->pos.y() << ")" << std::endl;
}

void Monster::setPositions() {
	this->pos.setX(rand() % 100);
	this->pos.setY(rand() % 100);
}
