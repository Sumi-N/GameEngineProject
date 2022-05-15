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
		LARGE_INTEGER lpPerformanceCount_begin;
		LARGE_INTEGER lpPerformanceCount_end;

		static LARGE_INTEGER LPFrequency;
		static double FrequencyPerMilliSecond;
#endif

	public:
		static void Init();
		static void Update(Time& io_time);

		static void Begin(Time& io_time);
		static void End(Time& io_time);
	};

	inline void Time::Init()
	{
#ifdef  ENGINE_PLATFORM_WINDOWS
		QueryPerformanceFrequency(&LPFrequency);
		FrequencyPerMilliSecond = double(LPFrequency.QuadPart) / 1000;
#endif
	}

	inline void Time::Update(Time& io_time)
	{
#ifdef  ENGINE_PLATFORM_WINDOWS
		QueryPerformanceCounter(&io_time.lpPerformanceCount_end);
		if (io_time.lpPerformanceCount_begin.QuadPart == 0)
			io_time.dt = 0;
		else
			io_time.dt = double(io_time.lpPerformanceCount_end.QuadPart - io_time.lpPerformanceCount_begin.QuadPart) / FrequencyPerMilliSecond;
		io_time.lpPerformanceCount_begin.QuadPart = io_time.lpPerformanceCount_end.QuadPart;
#endif
	}

	inline void Time::Begin(Time& io_time)
	{
#ifdef ENGINE_PLATFORM_WINDOWS
		QueryPerformanceCounter(&io_time.lpPerformanceCount_begin);
#endif // ENGINE_PLATFORM_WINDOWS
	}

	inline void Time::End(Time& io_time)
	{
#ifdef ENGINE_PLATFORM_WINDOWS
		QueryPerformanceCounter(&io_time.lpPerformanceCount_end);
		io_time.dt = double(io_time.lpPerformanceCount_end.QuadPart - io_time.lpPerformanceCount_begin.QuadPart) / FrequencyPerMilliSecond;
#endif // ENGINE_PLATFORM_WINDOWS
	}
}
