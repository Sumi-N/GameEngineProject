#pragma once
#include <PremadeParts/Skybox.h>
#include <Thread/Define.h>

namespace Tempest
{

	class MySkyBox : public SkyBox
	{
		int currentstate = 0;

		void Update(float) override;
	};

	inline void MySkyBox::Update(float i_dt)
	{
		if (UserInput.QueryKey(VirtualKey::KEY_1) == InputState::Pressed)
		{
			currentstate = 1;
		}
		if (UserInput.QueryKey(VirtualKey::KEY_2) == InputState::Pressed)
		{
			currentstate = 2;
		}

		if (UserInput.QueryKey(VirtualKey::KEY_3) == InputState::Pressed)
		{
			currentstate = 0;
		}
	}

}