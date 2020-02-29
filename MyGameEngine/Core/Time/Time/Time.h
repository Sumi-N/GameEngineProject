#pragma once

#define ENGINE_PLATFORM_WINDOWS

#ifdef  ENGINE_PLATFORM_WINDOWS
#include <Windows.h>
#endif

class Time
{
public:
	static double dt;

	static void Init();
	static void Update();

private:
	static double frequencypermillisecond;

#ifdef  ENGINE_PLATFORM_WINDOWS
	static LARGE_INTEGER lpFrequency;
	static LARGE_INTEGER lpPerformanceCount_begin;
	static LARGE_INTEGER lpPerformanceCount_end;
#endif
};

inline void Time::Init()
{
#ifdef  ENGINE_PLATFORM_WINDOWS
	QueryPerformanceFrequency(&Time::lpFrequency);
	Time::frequencypermillisecond = double(Time::lpFrequency.QuadPart) / 1000;
	Time::lpPerformanceCount_begin.QuadPart = 0;
#endif
}

inline void Time::Update()
{
#ifdef  ENGINE_PLATFORM_WINDOWS
	QueryPerformanceCounter(&Time::lpPerformanceCount_end);
	if (Time::lpPerformanceCount_begin.QuadPart == 0)
		Time::dt = 0;
	else
		Time::dt = double(Time::lpPerformanceCount_end.QuadPart - Time::lpPerformanceCount_begin.QuadPart) / Time::frequencypermillisecond;
	Time::lpPerformanceCount_begin.QuadPart = Time::lpPerformanceCount_end.QuadPart;
#endif
}

