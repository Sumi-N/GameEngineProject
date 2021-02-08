#pragma once
#include "Define.h"

namespace Tempest
{

	enum class InputState : uint8_t
	{
		Released = 0,
		Pressed = 1,
		Releasing = 2,
		Pressing = 3,
	};

	class Input
	{
	public:
		float X()
		{
			return xpos;
		}
		float Y()
		{
			return ypos;
		}
		float MouseVelocityX(float i_dt)
		{
			return (xpos - past_xpos) / i_dt;
		}
		float MouseVelocityY(float i_dt)
		{
			return (ypos - past_ypos) / i_dt;
		}

		void Init();
		InputState QueryKey(VirtualKey i_VKeyID);

	private:
		float xpos = 0, ypos = 0;
		float past_xpos = 0, past_ypos = 0;

		std::unordered_map<VirtualKey, bool> state;
		std::unordered_map<VirtualKey, bool> paststate;
		std::vector<std::pair<VirtualKey, bool>> pastkeys;

#ifdef ENGINE_PLATFORM_WINDOWS

	public:
		void InitForWindows(HWND);
		bool IsKeyPressed(VirtualKey);
		bool IsKeyReleased(VirtualKey);
		void Populate();

#endif // ENGINE_PLATFORM_WINDOWS
	private:
		HWND window_hanlder;
	};

}


