#pragma once

#include <Thread/Define.h>

namespace Tempest
{

	class MyPointLight : public PointLight
	{
		void Update(float i_dt) override;
	};

	inline void MyPointLight::Update(float i_dt)
	{


		if (UserInput.QueryKey(VirtualKey::KEY_I) == InputState::Pressing)
		{
			Translate(Vec3f(pos.x, pos.y + 1.0f, pos.z));
		}

		if (UserInput.QueryKey(VirtualKey::KEY_K) == InputState::Pressing)
		{
			Translate(Vec3f(pos.x, pos.y - 1.0f, pos.z));
		}

		if (UserInput.QueryKey(VirtualKey::KEY_J) == InputState::Pressing)
		{
			Translate(Vec3f(pos.x + 1.0f, pos.y, pos.z));
		}

		if (UserInput.QueryKey(VirtualKey::KEY_L) == InputState::Pressing)
		{
			Translate(Vec3f(pos.x - 1.0f, pos.y, pos.z));
		}

		// The update should happen later
		PointLight::Update(i_dt);
	}

}