#pragma once
#include "Vector2D.h"
#include "DebugLog.h"
#include "Object2D.h"
#include "SmartPointers.h"

//#define ENABLE_STATIC_FRICTION

class Physics2D
{
public:
	Physics2D();
	~Physics2D();

	void addForce(Vector2D<double, double>);
	void update(double i_dt);

public:
	Engine::OwningPointer<Object2D> pointer;

	double mass;
	double fric;
	double air_fric;
	Vector2D<double,double> vel; //velocity
	Vector2D<double,double> acc; //accelelation

#if defined(ENABLE_STATIC_FRICTION)
#define DYNAMIC_FRICTION fric
#define STATIC_FRICTION static_friction
	double static_fric;
#endif

private:
	Vector2D<double, double> old_vel;
};


inline Physics2D::Physics2D()
{
	mass = 1;
	air_fric = 0.02;
	vel.set(Vector2D<double, double>(0, 0));
	acc.set(Vector2D<double, double>(0, 0));
}

inline Physics2D::~Physics2D()
{
	//No need to delete object;
}

inline void Physics2D::addForce(Vector2D<double, double> i_force)
{
	assert(pointer);
	acc = acc + i_force / mass;
}

inline void Physics2D::update(double i_dt)
{
	assert(pointer);
	acc = acc - vel * air_fric;
	old_vel = vel;
	vel = vel + acc * i_dt;
	vel = (vel + old_vel) / 2;
	pointer->pos = pointer->pos + vel * i_dt;
	acc.set(Vector2D<double, double>(0, 0));

	//DEBUG_PRINT("the old velocity is %f", old_vel.x);
	//DEBUG_PRINT("the new velocity is %f", vel.x);
	//DEBUG_PRINT("the acc is %f", acc.x);
	//DEBUG_PRINT("the dt is %f", i_dt);
	return;
}

