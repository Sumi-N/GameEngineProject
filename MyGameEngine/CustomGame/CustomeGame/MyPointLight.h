#pragma once

#include <Parts/Light.h>
#include <Thread/Define.h>


class MyPointLight : public PointLight
{
	void Update(float i_dt) override;
};

inline void MyPointLight::Update(float i_dt)
{
	PointLight::Update(i_dt);

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_I, true))
	{
		Translate(Vec3f(pos.x, pos.y + 1.0f, pos.z));
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_K, true))
	{
		Translate(Vec3f(pos.x, pos.y - 1.0f, pos.z));
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_J, true))
	{
		Translate(Vec3f(pos.x, pos.y, pos.z + 1.0f));
	}

	if (UserInput.QueryKey((unsigned int)VirtualKey::KEY_L, true))
	{
		Translate(Vec3f(pos.x, pos.y, pos.z - 1.0f));
	}
}