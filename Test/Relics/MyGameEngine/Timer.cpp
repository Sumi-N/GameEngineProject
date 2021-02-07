#pragma once
#include "Time.h"

namespace Time {
	double frequencypermillisecond;
	LARGE_INTEGER lpFrequency;
	LARGE_INTEGER lpPerformanceCount_begin;
	LARGE_INTEGER lpPerformanceCount_end;
	double dt;
}