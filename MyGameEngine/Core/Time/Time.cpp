#pragma once
#include "Time.h"

#ifdef  ENGINE_PLATFORM_WINDOWS
double        Time::dt;
double        Time::frequencypermillisecond;
LARGE_INTEGER Time::lpFrequency;
LARGE_INTEGER Time::lpPerformanceCount_begin;
LARGE_INTEGER Time::lpPerformanceCount_end;
#endif