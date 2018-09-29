#include "Player.h"
#include <stdlib.h>
#include <iostream>



Player::Player()
{
}


Player::~Player()
{
}

void Player::setPositions() {
	this->pos.setX(rand() % 10);
	this->pos.setY(rand() % 10);
}

void Player::setName(char * input)
{
	name = input;
}

void Player::showName()
{
	for (int i = 0; i < namelength; i++) {
		printf("%c", name[i]);
	}
	printf("\n");
}

void Player::showPosition()
{
	for (int i = 0; i < namelength; i++) {
		printf("%c", name[i]);
	}
	std::cout << " is at (" << this->pos.x() << "," << this->pos.y() << ")" << std::endl;
}


bool Player::move(char order) {

	if (order == 'w' && this->pos.y() != 0) {
		int tmp = this->pos.y();
		tmp -= 1;
		this->pos.setY(tmp);
		return true;
	}
	else if (order == 'a' && this->pos.x() != 0) {
		int tmp = this->pos.x();
		tmp -= 1;
		this->pos.setX(tmp);
		return true;
	}
	else if (order == 's' && this->pos.y() != 100) {
		int tmp = this->pos.y();
		tmp += 1;
		this->pos.setY(tmp);
		return true;
	}
	else if (order == 'd' && this->pos.x() != 100) {
		int tmp = this->pos.x();
		tmp += 1;
		this->pos.setX(tmp);
		return true;
	}
	else {
		return false;
	}
}