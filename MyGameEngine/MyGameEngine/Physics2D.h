#pragma once
#include "Vector2D.h"
#include "DebugLog.h"
#include "Object2D.h"

//#define ENABLE_STATIC_FRICTION

class Physics2D
{
public:
	Physics2D();
	Physics2D(Object2D * obj);
	~Physics2D();

	void update(Vector2D<double, double> i_acc, double i_dt);

public:
	Object2D * obj;

	double mass;
	double friction;
	Vector2D<double,double> vel; //velocity
	Vector2D<double,double> acc; //accelelation

#if defined(ENABLE_STATIC_FRICTION)
#define DYNAMIC_FRICTION friction
#define STATIC_FRICTION static_friction
	double static_friction;
#endif

private:
	Vector2D<double, double> old_vel;
};


inline Physics2D::Physics2D()
{
	mass = 1;
	vel.set(Vector2D<double, double>(0, 0));
	acc.set(Vector2D<double, double>(0, 0));
}

inline Physics2D::Physics2D(Object2D * object) 
{
	mass = 1;
	vel.set(Vector2D<double, double>(0, 0));
	acc.set(Vector2D<double, double>(0, 0));
	obj = object;
}

inline Physics2D::~Physics2D()
{
	//No need to delete object;
}

inline void Physics2D::update(Vector2D<double, double> i_force, double i_dt)
{
	assert(obj);
	acc = i_force / mass;
	old_vel = vel;
	vel = vel + acc * i_dt;
	vel = (vel + old_vel) / 2;
	obj->pos = obj->pos + vel * i_dt;
	//DEBUG_PRINT("the old velocity is %f", old_vel.x);
	//DEBUG_PRINT("the new velocity is %f", i_vel.x);
	//DEBUG_PRINT("the acc is %f", i_acc.x);
	//DEBUG_PRINT("the dt is %f", i_dt);
	return;
}

