#pragma once
#include "Object2D.h"
#include "Vector3D.h"
#include "Matrix4.h"
#include <string>

class Object3D
{

public:
	Vector3D pos;
	Vector3D rot;
	std::string name;

	//For collision detection
	Vector3D extent_width;
	Vector3D extent_height;
	//Boundary boundary;     <- This is a depriciated membaer, the Boundary class moved to CollisionDetection.h 
	//void updateBoundary(); <- This is a depriciated membaer, the Boundary class moved to CollisionDetection.h 

	void info() const;
};

//inline void Object3D::updateBoundary()
//{
//	Vector3D center = pos + extent_height;
//	boundary.ur = center + Matrix4::Yaw(rot.z) * ( 1 * extent_width +  1 * extent_height);
//	boundary.ul = center + Matrix4::Yaw(rot.z) * (-1 * extent_width +  1 * extent_height);
//	boundary.lr = center + Matrix4::Yaw(rot.z) * ( 1 * extent_width + -1 * extent_height);
//	boundary.ll = center + Matrix4::Yaw(rot.z) * (-1 * extent_width + -1 * extent_height);
//}

inline void Object3D::info() const {
	//printf("%s is at (%f, %f, %f)", name, pos.x, pos.y, pos.z);
}