#pragma once
#include "Vector3D.h"
#include "Object3D.h"
#include "SmartPointers.h"
#include "DebugLog.h"

class Physics3D
{
public:
	Physics3D();
	Physics3D(const Physics3D &) = delete;
	~Physics3D();

	void addForce(Vector3D);
	void update(float i_dt);

public:
	Engine::OwningPointer<Object3D> pointer;

	float mass;
	float fric;
	float air_fric;
	Vector3D vel;
	Vector3D acc;

private:
	Vector3D old_vel;
};

inline Physics3D::Physics3D() {
	mass = 1.0f;
	air_fric = 0.02f;
	vel.set(0, 0, 0);
	acc.set(0, 0, 0);
}

inline Physics3D::~Physics3D() {

}

inline void Physics3D::addForce(Vector3D i_force) {
	assert(pointer);
	acc = acc + i_force / mass;
}

inline void Physics3D::update(float i_dt) {
	assert(pointer);
	acc = acc - air_fric * vel;
	old_vel = vel;
	vel = vel + i_dt * acc;
	vel = (vel + old_vel) / 2;
	pointer->pos = pointer->pos + i_dt * vel;

	//DEBUG_PRINT("the old velocity is %f", old_vel.x);
	//DEBUG_PRINT("the new velocity is %f", vel.x);
	//DEBUG_PRINT("the acc is %f", acc.x);
	//DEBUG_PRINT("the dt is %f", i_dt);

	acc.set(0, 0, 0);
	return;
}