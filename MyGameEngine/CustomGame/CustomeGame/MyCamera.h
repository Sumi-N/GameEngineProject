#pragma once
#include <Parts/Camera.h>
#include <Thread/Define.h>

class MyCamera :public Camera
{
	void Init() override;
	void Update(float i_dt) override;
};

inline void MyCamera::Init()
{
	Camera::Init();
}

inline void MyCamera::Update(float i_dt)
{
	Camera::Update(i_dt);

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_W, true))
	{
		MoveCamera(-0.01f, forwardvec);
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_S, true))
	{
		MoveCamera(0.01f, forwardvec);
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_A, true))
	{
		MoveCamera(-0.01f, rightvec);
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_D, true))
	{
		MoveCamera(0.01f, rightvec);
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_SPACE, true))
	{
		Vec3f zero; zero.Zero();
		MoveCamera(0, zero);
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_RIGHTBUTTON, true))
	{
		Vec3f up = Vec3f(0, 1, 0);
		Vec3f right = rightvec;

		if (UserInput.xpos - UserInput.past_xpos > 0)
		{
			RotateAround(-1, up);
		}
		else if (UserInput.xpos - UserInput.past_xpos < 0)
		{
			RotateAround(1, up);
		}

		if (UserInput.ypos - UserInput.past_ypos > 0)
		{
			RotateAround(-1, right);
		}
		else if (UserInput.ypos - UserInput.past_ypos < 0)
		{
			RotateAround(1, right);
		}
	}
}