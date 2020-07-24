#pragma once
#include "Input.h"

#ifdef ENGINE_PLATFORM_WINDOWS

//#include <WinUser.h>
#pragma comment( lib, "User32.lib" )

void Input::QueryInputs()
{
	//for (int i = 0; i < 256; i++)
	//{
	//	paststate.at(i) = state.at(i);
	//}
	
}

#endif // ENGINE_PLATFORM_WINDOWS




