#pragma once

namespace MEG {
	void ConsolePrint(const char *i_fmt, ...);
}

#if defined(__DEBUG_BUILD__) && !defined(__RELEASE_BUILD__)
# define DEBUG_PRINT(fmt,...) MEG::ConsolePrint((fmt),__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt,...) void(0)
#endif
