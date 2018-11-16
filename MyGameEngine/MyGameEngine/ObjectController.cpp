#include "ObjectController.h"



ObjectController::ObjectController(Object2D obj)
{
	this->object = obj;
}


ObjectController::~ObjectController()
{
}

bool ObjectController::moveTowardObject(Object2D & target)
{
	this->object.setPosition(target.getPosition());
	return true;
}

bool ObjectController::moveByOrder(const char order)
{
	return false;
}
