#pragma once
#include "Object2D.h"
class Player : public Object2D
{
public:
	Player() {};
	~Player() {};
	void setPositions();
	void setName(char*);
	void showName() override;
	void showPosition() override;
	const bool move(const char);
};

inline void Player::setPositions() {
	this->pos.setX(rand() % 10);
	this->pos.setY(rand() % 10);
}

inline void Player::setName(char * input)
{
	name = input;
}

inline void Player::showName()
{
	for (int i = 0; i < namelength; i++) {
		printf("%c", name[i]);
	}
	printf("\n");
}

inline void Player::showPosition()
{
	for (int i = 0; i < namelength; i++) {
		printf("%c", name[i]);
	}
	std::cout << " is at (" << this->pos.x() << "," << this->pos.y() << ")" << std::endl;
}


inline const bool Player::move(const char order) {

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