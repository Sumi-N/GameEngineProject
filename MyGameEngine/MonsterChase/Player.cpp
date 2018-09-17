#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
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