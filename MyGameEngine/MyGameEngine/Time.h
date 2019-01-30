#include "DebugLog.h"

#include <Windows.h>

namespace Time {
	static double frequencypermillisecond;
	static LARGE_INTEGER lpFrequency;
	static LARGE_INTEGER lpPerformanceCount_begin;
	static LARGE_INTEGER lpPerformanceCount_end;
	static double dt;
}

class Timer {
public:
	inline static void Init() {
		QueryPerformanceFrequency(&Time::lpFrequency);
		Time::frequencypermillisecond = double(Time::lpFrequency.QuadPart)/1000;
		//DEBUG_PRINT("%f",frequencypermillisecond);

		Time::lpPerformanceCount_begin.QuadPart = 0;
	}

	inline static void Run()
	{
		QueryPerformanceCounter(&Time::lpPerformanceCount_end);
		if (Time::lpPerformanceCount_begin.QuadPart == 0) {
			Time::dt = 0;
		}
		else {
			Time::dt = double(Time::lpPerformanceCount_end.QuadPart - Time::lpPerformanceCount_begin.QuadPart) / Time::frequencypermillisecond;
		}
		//DEBUG_PRINT("%f", dt);
		Time::lpPerformanceCount_begin.QuadPart = Time::lpPerformanceCount_end.QuadPart;
		//Sleep(1000);
	}
};