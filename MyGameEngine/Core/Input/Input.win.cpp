#pragma once
#include "Input.h"

#ifdef ENGINE_PLATFORM_WINDOWS

#include <WinUser.h>

void Input::QueryInputs()
{
	for (int i = 0; i < 256; i++)
	{
		paststate.at(i) = state.at(i);
	}
}

#endif // ENGINE_PLATFORM_WINDOWS




