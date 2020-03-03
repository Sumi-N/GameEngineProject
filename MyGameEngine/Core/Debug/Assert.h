#pragma once
#include <sstream>
#include <intrin.h>

#include "Define.h"

#ifdef ENGINE_PLATFORM_WINDOWS
	#include <intrin.h>
	#include <Windows.h>
#endif

namespace DEBUG
{
	bool AssertionCheck(const unsigned int i_linenumber, const char* const i_file, const char* const i_message, bool& i_ignorethisinthefuture, ...);
	bool AssertionCheckPlatoformSpecific(std::ostringstream& io_message, bool& i_ignorethisinthefuture);
}

#if defined(_DEBUG)
#define DEBUG_ASSERT(i_assertion)\
	{\
		static auto ignorethisinthefuture = false;\
		if( static_cast<bool>(i_assertion) && AssertionCheck(__LINE__, __FILE__, "", ignorethisinthefuture, __VA_ARGS__))\
		{\
			__debugbreak();\
		}\
	}
#else
#define DEBUG_ASSERT()
#endif //  defined(_DEBUG)


