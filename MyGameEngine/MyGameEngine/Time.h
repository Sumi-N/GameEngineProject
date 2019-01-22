#include "DebugLog.h"

#include <Windows.h>

static double frequencypermillisecond;
static LARGE_INTEGER lpFrequency;
static LARGE_INTEGER lpPerformanceCount_begin;
static LARGE_INTEGER lpPerformanceCount_end;
static double dt;

class Timer {
public:
	inline static void Init() {
		QueryPerformanceFrequency(&lpFrequency);
		frequencypermillisecond = double(lpFrequency.QuadPart)/1000;
		//DEBUG_PRINT("%f",frequencypermillisecond);

		lpPerformanceCount_begin.QuadPart = 0;
	}

	inline static void Run()
	{
		QueryPerformanceCounter(&lpPerformanceCount_end);
		if (lpPerformanceCount_begin.QuadPart == 0) {
			dt = 0;
		}
		else {
			dt = double(lpPerformanceCount_end.QuadPart - lpPerformanceCount_begin.QuadPart) / frequencypermillisecond;
		}
		//DEBUG_PRINT("%f", dt);
		lpPerformanceCount_begin.QuadPart = lpPerformanceCount_end.QuadPart;
		//Sleep(1000);
	}
};