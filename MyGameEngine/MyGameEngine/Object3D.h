#pragma once
#include "Object2D.h"
#include "Vector3D.h"
#include <string>

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

	void info() const;
};

inline void Object3D::info() const {
	//printf("%s is at (%f, %f, %f)", name, pos.x, pos.y, pos.z);
}