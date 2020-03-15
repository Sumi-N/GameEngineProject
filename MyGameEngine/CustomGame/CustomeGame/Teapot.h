#pragma once
#include <Parts/Object.h>
#include <Core/Math/Vector.h>

class Teapot : public Object 
{
	void Init() override;
	void Update(float i_dt) override;
};

inline void Teapot::Init()
{
	this->pos = Vec3f(0, 0, -50);
}

inline void Teapot::Update(float i_dt)
{

}