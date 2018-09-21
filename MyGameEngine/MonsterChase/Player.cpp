#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::setPositions() {
	this->pos.setX(rand() % 3);
	this->pos.setY(rand() % 3);
}

Vector2D<int, int> Player::returnPos()
{
	return pos;
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