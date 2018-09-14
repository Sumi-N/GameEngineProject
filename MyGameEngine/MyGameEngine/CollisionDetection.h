#pragma once
#include "Object2D.h"
#include "List.h"
class CollisionDetection
{
public:
	CollisionDetection();
	~CollisionDetection();
	void add(Object2D obj);
private:
	List<Object2D> collision;
};

