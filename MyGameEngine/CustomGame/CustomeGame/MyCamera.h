#pragma once
#include <Parts/Camera.h>
#include <Thread/Define.h>

class MyCamera :public Camera
{
public:
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

	if (UserInput.QueryKey(VirtualKey::KEY_W) == InputState::Pressing)
	{
		MoveCamera(0.01f, forwardvec);
	}

	if (UserInput.QueryKey(VirtualKey::KEY_S) == InputState::Pressing)
	{
		MoveCamera(-0.01f, forwardvec);
	}

	if (UserInput.QueryKey(VirtualKey::KEY_A) == InputState::Pressing)
	{
		MoveCamera(-0.01f, rightvec);
	}

	if (UserInput.QueryKey(VirtualKey::KEY_D) == InputState::Pressing)
	{
		MoveCamera(0.01f, rightvec);
	}

	if (UserInput.QueryKey(VirtualKey::KEY_Q) == InputState::Pressing)
	{
		MoveCamera(0.01f, upvec);
	}

	if (UserInput.QueryKey(VirtualKey::KEY_E) == InputState::Pressing)
	{
		MoveCamera(-0.01f, upvec);
	}

	if (UserInput.QueryKey(VirtualKey::KEY_RIGHTBUTTON) == InputState::Pressing)
	{
		Vec3f up = Vec3f(0, 1, 0);
		Vec3f right = rightvec;

		if (UserInput.MouseVelocityX() > 0)
		{
			RotateAround(1, up);
		}
		else if (UserInput.MouseVelocityX() < 0)
		{
			RotateAround(-1, up);
		}

		if (UserInput.MouseVelocityY() > 0)
		{
			RotateAround(1, right);
		}
		else if (UserInput.MouseVelocityY() < 0)
		{
			RotateAround(-1, right);
		}
	}

	UserInput.QueryInputs();
}