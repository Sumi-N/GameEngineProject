#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

int Player::getPositionX() {
	return x;
}

int Player::getPositionY() {
	return y;
}

void Player::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}


bool Player::move(char order){
	if (order == 'w' && this->y != 0) {
		this->y--;
		return true;;
	}
	else if (order == 'a' && this->x != 0) {
		this->x--;
		return true;;
	}
	else if (order == 's' && this->y != 100) {
		this->y++;
		return true;
	}
	else if (order == 'd' && this->x != 100) {
		this->x++;
		return true;
	}
	else {
		return false;
	}
}