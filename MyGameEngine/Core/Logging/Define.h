#pragma once
#include <Configuration/Configuration.h>

#pragma comment( lib, "User32.lib" )

#include <sstream>

#ifdef ENGINE_PLATFORM_WINDOWS
	#include <intrin.h>
	#include <Windows.h>
#endif