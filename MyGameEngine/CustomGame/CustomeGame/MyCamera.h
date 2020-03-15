#pragma once
#include <Parts/Camera.h>

class MyCamera :public Camera
{
	void Init() override;
	void Update(float i_dt) override;
};

inline void MyCamera::Init()
{

}

inline void MyCamera::Update(float i_dt)
{
	Camera::Update(i_dt);
}