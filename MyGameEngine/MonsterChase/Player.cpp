#include "Player.h"
#include <stdlib.h>



Player::Player()
{
}


Player::~Player()
{
}

void Player::setPositions() {
	this->pos.setX(rand() % 100);
	this->pos.setY(rand() % 100);
}

void Player::setName(char * input)
{
	name = input;
}

void Player::showName()
{
	for (int i = 0; i < 255; i++) {
		printf("%c", name[i]);
	}
	printf("\n");
}


bool Player::move(char order) {
	if (order == 'w' && this->pos.y() != 0) {
		int tmp = this->pos.y();
		this->pos.setY(tmp--);
		return true;
	}
	else if (order == 'a' && this->pos.x() != 0) {
		int tmp = this->pos.x();
		this->pos.setX(tmp--);
		return true;
	}
	else if (order == 's' && this->pos.y() != 100) {
		int tmp = this->pos.y();
		this->pos.setX(tmp++);
		return true;
	}
	else if (order == 'd' && this->pos.x() != 100) {
		int tmp = this->pos.x();
		this->pos.setX(tmp++);
		return true;
	}
	else {
		return false;
	}
}