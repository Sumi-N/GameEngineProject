#pragma once
#include "Object2D.h"
#include "Vector3D.h"
#include <string>

class Object3D
{
	struct AABB {
		Vector3D center;
		Vector3D extent;
	};

public:
	Vector3D pos;
	std::string name;
	AABB aabb;

	void info() const;
};

inline void Object3D::info() const {
	//printf("%s is at (%f, %f, %f)", name, pos.x, pos.y, pos.z);
}