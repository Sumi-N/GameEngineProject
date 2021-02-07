#pragma once
#include <Parts/Camera.h>
#include <Thread/Define.h>
#include <Application/Define.h>

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

	if (UserInput.QueryKey(VirtualKey::KEY_SPACE) == InputState::Released)
	{
		if(Entity::Cameras.size() != 0 && Entity::Cameras.size() !=1)
			Entity::SwapCamera(0, 1);
	}

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
		Vec2f mousevelocity = Vec2f(UserInput.MouseVelocityX(i_dt), UserInput.MouseVelocityY(i_dt));

		Vec3f up = Vec3f(0, 1, 0);
		RotateAround(mousevelocity.x, up);
		Vec3f right = GetRightVec();
		RotateAround(mousevelocity.y, right);
	}
}