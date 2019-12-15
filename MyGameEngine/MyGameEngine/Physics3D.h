#pragma once

//#include <Core/Math/Vector.h>
#include "../Core/Math/Vector.h"

#include "Object3D.h"
#include "SmartPointers.h"
#include "Delegates.h"
#include "DebugLog.h"

__declspec(align(16))  class Physics3D
{
public:
	Physics3D();
	Physics3D(const Physics3D &) = delete;
	~Physics3D();

	void addForce(Vec3f);
	void update(const float);
	void updatePosition(const float);
	void updateRotation(const float);
	
	virtual void init();
	virtual void collision(Physics3D *);

public:
	Engine::OwningPointer<Object3D> pointer;

	float mass;
	float fric;
	float air_fric;
	Vec3f vel;
	Vec3f acc;
	Vec3f ang_vel;
	Vec3f ang_acc;

	void* operator new(size_t);
	void operator delete(void *);

private:
	Vec3f old_vel;	
};

inline Physics3D::Physics3D()
	: mass(1.0f), air_fric(0.02f){}

inline Physics3D::~Physics3D() {}

inline void Physics3D::addForce(Vec3f i_force) {
	assert(pointer);
	acc += i_force / mass;
}

inline void Physics3D::update(const float i_dt) {
	assert(pointer);

	updatePosition(i_dt);
	updateRotation(i_dt);

	//DEBUG_PRINT("the old velocity is %f", old_vel.x);
	//DEBUG_PRINT("the new velocity is %f", vel.x);
	//DEBUG_PRINT("the acc is %f", acc.x);
	//DEBUG_PRINT("the dt is %f", i_dt);

	return;
}

inline void Physics3D::updatePosition(const float i_dt)
{
	acc = acc - air_fric * vel;
	old_vel = vel;
	vel = vel + acc;
	vel = (vel + old_vel) / 2;
	pointer->pos = pointer->pos + i_dt * vel;
	acc.Zero();
}

inline void Physics3D::updateRotation(const float)
{
}

inline void Physics3D::init() {

}

inline void Physics3D::collision(Physics3D *)
{
	DEBUG_PRINT("Calling physics3d collision");
}

inline void * Physics3D::operator new(size_t i)
{
	return _mm_malloc(i,16);
}

inline void Physics3D::operator delete(void * p)
{
	_mm_free(p);
}
