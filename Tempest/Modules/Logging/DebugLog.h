#pragma once
#include "Define.h"

namespace LOG
{
	void ConsolePrint(const char *i_fmt, ...);
}

#if defined(_DEBUG) && !defined(NDEBUG)
# define DEBUG_PRINT(fmt,...) LOG::ConsolePrint((fmt),__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt,...) void(0)
#endif
