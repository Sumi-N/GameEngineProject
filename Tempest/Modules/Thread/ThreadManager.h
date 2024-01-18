#pragma once
#include "Define.h"

namespace Tempest
{
	class Thread;

	constexpr uint32_t s_MaxThreadCount = 24;

	class ThreadManager
	{
	public:
		static uint8_t RegisterThread(Thread*);
		static void PropagateEndSignal();

		static void SyncPoint1(uint8_t thread_id);
		static void SyncPoint2(uint8_t thread_id);
	};
}