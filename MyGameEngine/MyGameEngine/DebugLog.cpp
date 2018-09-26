#include "DebugLog.h"
#include <assert.h>
#include <stdio.h>

namespace {

	void ConsolePrint(const char *i_fmt, ...) {
		assert(i_fmt);

		const size_t lentemp = 256;
		char strTemp[lentemp] = "Log:";

		//strcat_s()
	}
}