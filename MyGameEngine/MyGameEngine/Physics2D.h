#pragma once
#include "Vector2D.h"
#include "DebugLog.h"

class Physics2D
{
public:
	Physics2D();
	~Physics2D();

	void Update(Vector2D<double, double>& i_pos, Vector2D<double, double>& i_vel, Vector2D<double, double> i_acc, double i_dt);
};


inline Physics2D::Physics2D()
{
}

inline Physics2D::~Physics2D()
{
}

inline void Physics2D::Update(Vector2D<double, double>& i_pos, Vector2D<double, double>& i_vel, Vector2D<double, double> i_acc, double i_dt)
{
	Vector2D<double, double> old_vel = i_vel;
	i_vel = i_vel + i_acc * i_dt;
	i_vel = (i_vel + old_vel)/2;
	i_pos = i_pos + i_vel * i_dt;
	//DEBUG_PRINT("the old velocity is %f", old_vel.x());
	DEBUG_PRINT("the new velocity is %f", i_vel.x());
	//DEBUG_PRINT("the acc is %f", i_acc.x());
	//DEBUG_PRINT("the dt is %f", i_dt);
	return;
}

