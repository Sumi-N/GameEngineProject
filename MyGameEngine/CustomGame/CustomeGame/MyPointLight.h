#pragma once

#include <Parts/Light.h>
#include <Thread/Define.h>


class MyPointLight : public PointLight
{
	void Update(float i_dt) override;
};

inline void MyPointLight::Update(float i_dt)
{


	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_I) == InputState::Pressed)
	{
		Translate(Vec3f(pos.x, pos.y + 1.0f, pos.z));
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_K) == InputState::Pressed)
	{
		Translate(Vec3f(pos.x, pos.y - 1.0f, pos.z));
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_J) == InputState::Pressed)
	{
		Translate(Vec3f(pos.x + 1.0f, pos.y, pos.z));
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_L) == InputState::Pressed)
	{
		Translate(Vec3f(pos.x - 1.0f, pos.y, pos.z));
	}

	// The update should happen later
	PointLight::Update(i_dt);
}