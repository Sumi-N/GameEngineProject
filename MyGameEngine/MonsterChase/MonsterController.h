#pragma once
#include <stdlib.h>
#include "ObjectController.h"

class MonsterController : public ObjectController
{
public:
	MonsterController(Object2D obj)
		: ObjectController(obj) {
	}
	bool moveRandomly();
};

inline bool MonsterController::moveRandomly(){
	bool up = true, down = true, right = true, left = true;
	if (this->object.pos.x() == 0) {
		left = false;
	}
	else if (this->object.pos.x() == 100) {
		right = false;
	}
	if (this->object.pos.y() == 0) {
		up = false;
	}
	else if (this->object.pos.y() == 100) {
		down = false;
	}

	if (right && left) {
		object.pos.setX(rand() % 2 ? object.pos.x() + 1 : object.pos.x() - 1);
	}
	else {
		object.pos.setX(right ? object.pos.x() + 1 : object.pos.x() - 1);
	}

	if (up && down) {
		object.pos.setY(rand() % 2 ? object.pos.y() + 1 : object.pos.y() - 1);
	}
	else {
		object.pos.setY(up ? object.pos.y() + 1 : object.pos.y() - 1);
	}
	return true;
}