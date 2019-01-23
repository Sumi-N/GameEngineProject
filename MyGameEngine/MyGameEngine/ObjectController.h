#pragma once
#include "Object2D.h"

class ObjectController
{
public:
	ObjectController(Object2D * obj);
	~ObjectController();

	//Object2D object;
	Object2D * object;
	virtual bool moveTowardObject(Object2D & target);
	virtual bool moveByOrder(const char order);
private:

};

inline ObjectController::ObjectController(Object2D * obj)
{
	this->object = obj;
}


inline ObjectController::~ObjectController()
{
}

inline bool ObjectController::moveTowardObject(Object2D & target)
{
	this->object->setPosition(target.getPosition());
	return true;
}

inline bool ObjectController::moveByOrder(const char order)
{
	return false;
}