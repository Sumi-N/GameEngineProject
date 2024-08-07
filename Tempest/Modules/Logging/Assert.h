#pragma once

#include "Define.h"

namespace LOG
{
	bool AssertionCheck(const unsigned int i_linenumber, const char* const i_file, const char* const i_message, bool& i_ignorethisinthefuture, ...);
	bool AssertionCheckPlatoformSpecific(std::ostringstream& io_message, bool& i_ignorethisinthefuture);
}

#define ENGINE_ASSERT(i_assertion)\
	{\
		static auto ignorethisinthefuture = false;\
		if( !static_cast<bool>(i_assertion) && LOG::AssertionCheck(__LINE__, __FILE__, "", ignorethisinthefuture, ignorethisinthefuture) )\
		{\
			__debugbreak();\
		}\
	}

#define ENGINE_ASSERT_WITHMESSAGE(i_assertion, i_messagetodisplay, ...)\
	{\
		static auto ignorethisinthefuture = false;\
		if( !static_cast<bool>(i_assertion) && LOG::AssertionCheck(__LINE__, __FILE__, i_messagetodisplay, ignorethisinthefuture, __VA_ARGS__) )\
		{\
			__debugbreak();\
		}\
	}

#if defined(_DEBUG)
// If this true then the program will be halt
#define DEBUG_ASSERT(i_assertion)\
	{\
		static auto ignorethisinthefuture = false;\
		if( !static_cast<bool>(i_assertion) && LOG::AssertionCheck(__LINE__, __FILE__, "", ignorethisinthefuture, ignorethisinthefuture) )\
		{\
			__debugbreak();\
		}\
	}

#define DEBUG_ASSERT_WITHMESSAGE(i_assertion, i_messagetodisplay, ...)\
	{\
		static auto ignorethisinthefuture = false;\
		if( !static_cast<bool>(i_assertion) && LOG::AssertionCheck(__LINE__, __FILE__, i_messagetodisplay, ignorethisinthefuture, __VA_ARGS__) )\
		{\
			__debugbreak();\
		}\
	}
#else
#define DEBUG_ASSERT(i_assertion) void(0);
#define DEBUG_ASSERT_WITHMESSAGE(i_assertion, i_messagetodisplay, ...) void(0);
#endif //  defined(_DEBUG)