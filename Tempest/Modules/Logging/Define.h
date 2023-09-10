#pragma once

#include <Configuration/Configuration.h>

#pragma comment( lib, "User32.lib" )

#include <cstdarg>
#include <cstdio>
#include <sstream>

#ifdef ENGINE_PLATFORM_WINDOWS
	#include <assert.h>
	#include <intrin.h>
	#include <Windows.h>
	#include <stdio.h>
	#include <stdarg.h>
	#include <string.h>
#endif