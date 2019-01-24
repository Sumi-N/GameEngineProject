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

	Object2D * object;
	double mass=0;
	double friction;
	double velocity;
	double acceleration;

#if defined(ENABLE_STATIC_FRICTION)
#define DYNAMIC_FRICTION friction
#define STATIC_FRICTION static_friction
	double static_friction;
#endif

	void Update(Vector2D<double, double>& i_pos, Vector2D<double, double>& i_vel, Vector2D<double, double> i_acc, double i_dt);
};


inline Physics2D::Physics2D()
{
}

inline Physics2D::Physics2D(Object2D * obj) {
	object = obj;
}

inline Physics2D::~Physics2D()
{
}

inline void Physics2D::Update(Vector2D<double, double>& i_pos, Vector2D<double, double>& i_vel, Vector2D<double, double> i_acc, double i_dt)
{
	Vector2D<double, double> old_vel = i_vel;
	i_vel = i_vel + i_acc * i_dt;
	i_vel = (i_vel + old_vel) / 2;
	i_pos = i_pos + i_vel * i_dt;
	//DEBUG_PRINT("the old velocity is %f", old_vel.x());
	//DEBUG_PRINT("the new velocity is %f", i_vel.x());
	//DEBUG_PRINT("the acc is %f", i_acc.x());
	//DEBUG_PRINT("the dt is %f", i_dt);
	return;
}

