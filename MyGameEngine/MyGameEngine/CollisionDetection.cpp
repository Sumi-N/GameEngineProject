#include "CollisionDetection.h"



CollisionDetection::CollisionDetection()
{
}


CollisionDetection::~CollisionDetection()
{
}

/*
void CollisionDetection::add(const Object2D &_obj)
{
	collision.add(_obj);
}
*/

void CollisionDetection::add(Object2D* _obj) {
	collision.add(_obj);
}

/*
Object2D* CollisionDetection::check() {

}
*/
