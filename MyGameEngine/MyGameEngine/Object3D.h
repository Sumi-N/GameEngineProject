#pragma once
#include "Object2D.h"
#include "Vector3D.h"
#include <string>

class Object3D : public Object2D
{
public:
	Vector3D pos;
	std::string name;

	void info() const;
};

inline void Object3D::info() const {
	printf("%s is at (%f, %f, %f)", name, pos.x, pos.y, pos.z);
}