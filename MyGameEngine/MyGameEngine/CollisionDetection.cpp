#include "CollisionDetection.h"



CollisionDetection::CollisionDetection()
{
	printf("this call is not valid construcotr");
}


CollisionDetection::~CollisionDetection()
{
}

void CollisionDetection::add(Object2D obj)
{
	collision.add(obj);
}
