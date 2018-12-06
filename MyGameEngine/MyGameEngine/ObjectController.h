#pragma once
#include "Object2D.h"

class ObjectController
{
public:
	ObjectController(Object2D obj);
	~ObjectController();
	
	Object2D object;
	virtual bool moveTowardObject(Object2D & target);
	virtual bool moveByOrder(const char order);
private:

};

