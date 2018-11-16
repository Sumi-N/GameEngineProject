#pragma once
#include "ObjectController.h"

class PlayerController : public ObjectController
{
public:
	PlayerController(Object2D obj)
		: ObjectController(obj) {

	}
	bool moveByOrder(const char order) override;
};

inline bool PlayerController::moveByOrder(const char order) {

	if (order == 'w' && this->object.pos.y() != 0) {
		int tmp = this->object.pos.y();
		tmp -= 1;
		this->object.pos.setY(tmp);
		return true;
	}
	else if (order == 'a' && this->object.pos.x() != 0) {
		int tmp = this->object.pos.x();
		tmp -= 1;
		this->object.pos.setX(tmp);
		return true;
	}
	else if (order == 's' && this->object.pos.y() != 100) {
		int tmp = this->object.pos.y();
		tmp += 1;
		this->object.pos.setY(tmp);
		return true;
	}
	else if (order == 'd' && this->object.pos.x() != 100) {
		int tmp = this->object.pos.x();
		tmp += 1;
		this->object.pos.setX(tmp);
		return true;
	}
	else {
		return false;
	}
}