#pragma once

#include <Configuration/Configuration.h>

#pragma comment( lib, "User32.lib" )

#include <sstream>
#include <cstdarg>
#include <cstdio>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <Windows.h>

#ifdef ENGINE_PLATFORM_WINDOWS
	#include <intrin.h>
	#include <Windows.h>
#endif