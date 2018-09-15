#pragma once
#include "Object2D.h"
#include "List.h"
class CollisionDetection
{
public:
	CollisionDetection();
	~CollisionDetection();
	//void add(const Object2D &_obj);
	void add(Object2D* _obj);
	Object2D* check();
private:
	//List<Object2D> collision;
	List<Object2D*> collision;
};

