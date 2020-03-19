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

}

inline void MyCamera::Update(float i_dt)
{
	Camera::Update(i_dt);

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_W, true))
	{
		//DEBUG_PRINT("I'm pressing W key");
		MoveCamera(0.01f, forwardvec);
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_S, true))
	{
		//DEBUG_PRINT("I'm pressing S key");
		MoveCamera(-0.01f, forwardvec);
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_A, true))
	{
		//DEBUG_PRINT("I'm pressing A key");
		MoveCamera(-0.01f, rightvec);
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_D, true))
	{
		//DEBUG_PRINT("I'm pressing D key");
		MoveCamera(0.01f, rightvec);
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_SPACE, true))
	{
		//DEBUG_PRINT("I'm pressing Space key");
		Vec3f zero; zero.Zero();
		MoveCamera(0, zero);
	}
}