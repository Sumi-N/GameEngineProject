#pragma once
#include "Input.h"

#ifdef ENGINE_PLATFORM_WINDOWS

#include <Windows.h>


bool Input::IsKeyPressed(VirtualKey i_keyCode)
{
	const auto keyState = GetAsyncKeyState(static_cast<uint_fast8_t>(i_keyCode));
	const short isKeyDownMask = ~1;

	return (keyState & isKeyDownMask) != 0;
}

bool Input::IsKeyReleased(VirtualKey i_keyCode)
{
	const auto keyState = GetAsyncKeyState(static_cast<uint_fast8_t>(i_keyCode));
	const short isKeyDownMask = ~1;

	return (keyState & isKeyDownMask) == 0;
}

void Input::Populate()
{
	POINT mouse;
	GetCursorPos(&mouse);

	if (mouse.x != -1 && mouse.y != -1)
	{
		past_xpos = xpos; past_ypos = ypos;
		xpos = static_cast<float>(mouse.x); 
		ypos = static_cast<float>(mouse.y);
	}
	else
	{
		past_xpos = xpos; past_ypos = ypos;
	}

	for(size_t i = 0; i < 256; i++)
	{
		VirtualKey vkey = static_cast<VirtualKey>(i);

		paststate.at(vkey) = state.at(vkey);

		if (IsKeyPressed(vkey))
		{
			state.at(vkey) = true;
		}
		else if(IsKeyReleased(vkey))
		{
			state.at(vkey) = false;
		}
	}
}

#endif // ENGINE_PLATFORM_WINDOWS




