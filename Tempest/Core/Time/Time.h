#pragma once

#include "Define.h"

namespace Tempest
{
	class Time
	{
	public:
		Time() = default;	
		double dt;		

	private:
#ifdef  ENGINE_PLATFORM_WINDOWS
		double frequencypermillisecond;
		LARGE_INTEGER lpFrequency;
		LARGE_INTEGER lpPerformanceCount_begin;
		LARGE_INTEGER lpPerformanceCount_end;
#endif

	public:
		static void Init(Time& io_time);
		static void Update(Time& io_time);
	};

	inline void Time::Init(Time& io_time)
	{
#ifdef  ENGINE_PLATFORM_WINDOWS
		QueryPerformanceFrequency(&io_time.lpFrequency);
		io_time.frequencypermillisecond = double(io_time.lpFrequency.QuadPart) / 1000;
		io_time.lpPerformanceCount_begin.QuadPart = 0;
#endif
	}

	inline void Time::Update(Time& io_time)
	{
#ifdef  ENGINE_PLATFORM_WINDOWS
		QueryPerformanceCounter(&io_time.lpPerformanceCount_end);
		if (io_time.lpPerformanceCount_begin.QuadPart == 0)
			io_time.dt = 0;
		else
			io_time.dt = double(io_time.lpPerformanceCount_end.QuadPart - io_time.lpPerformanceCount_begin.QuadPart) / io_time.frequencypermillisecond;
		io_time.lpPerformanceCount_begin.QuadPart = io_time.lpPerformanceCount_end.QuadPart;
#endif
	}
}
