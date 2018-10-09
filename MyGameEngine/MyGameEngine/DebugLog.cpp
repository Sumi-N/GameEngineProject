#include "DebugLog.h"
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <Windows.h>

namespace MEG{

	void ConsolePrint(const char *i_fmt, ...) {
		assert(i_fmt);

		const size_t lentemp = 256;
		char strtemp[lentemp] = "Log:";

		strcat_s(strtemp, i_fmt);
		strcat_s(strtemp, "\n");

		const size_t lenoutput = lentemp + 32;
		char stroutput[lenoutput];

		va_list args;

		va_start(args, i_fmt);

		vsprintf_s(stroutput, lenoutput, strtemp, args);

		va_end(args);

		OutputDebugStringA(stroutput);
	}
}