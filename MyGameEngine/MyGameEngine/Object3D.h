#pragma once
#include "Object2D.h"
#include "Vector3D.h"
#include "Matrix4.h"
#include <string>

// For Collision Detection
struct Boundary
{
	Vector3D ur; // Upper right
	Vector3D ul; // Upper left
	Vector3D lr; // Lower right
	Vector3D ll; // Lower left
};

class Object3D
{
	struct AABB {
		Vector3D extent_width;
		Vector3D extent_height;
	};

public:
	Vector3D pos;
	Vector3D rot;
	std::string name;
	AABB aabb;
	Boundary boundary;

	void updateBoundary();
	void info() const;
};

inline void Object3D::updateBoundary()
{
	Vector3D center = pos + aabb.extent_height;
	boundary.ur = center + Matrix4::Yaw(rot.z) * ( 1 * aabb.extent_width +  1 * aabb.extent_height);
	boundary.ul = center + Matrix4::Yaw(rot.z) * (-1 * aabb.extent_width +  1 * aabb.extent_height);
	boundary.lr = center + Matrix4::Yaw(rot.z) * ( 1 * aabb.extent_width + -1 * aabb.extent_height);
	boundary.ll = center + Matrix4::Yaw(rot.z) * (-1 * aabb.extent_width + -1 * aabb.extent_height);
}

inline void Object3D::info() const {
	//printf("%s is at (%f, %f, %f)", name, pos.x, pos.y, pos.z);
}