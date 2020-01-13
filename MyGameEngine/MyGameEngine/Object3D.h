#pragma once

//#include <Core/Math/Vector.h>
#include "../Core/Math/Vector.h"

#include "Object2D.h"
#include <string>

__declspec(align(16))  class Object3D
{

public:
	Vec3f pos;
	Vec3f rot;
	std::string name;

	//For collision detection
	Vec3f extent_width;
	Vec3f extent_height;

	void* operator new(size_t);
	void operator delete(void *);

	void info() const;

	virtual void init();
	virtual void update();
};

inline void * Object3D::operator new(size_t i)
{
	return _mm_malloc(i, 16);
}

inline void Object3D::operator delete(void * p)
{
	_mm_free(p);
}

inline void Object3D::info() const {
	//printf("%s is at (%f, %f, %f)", name, pos.x, pos.y, pos.z);
}

inline void Object3D::init() {
	//DEBUG_PRINT("Calling object3d init");
}

inline void Object3D::update()
{
	//DEBUG_PRINT("Calling object3d update");
}
