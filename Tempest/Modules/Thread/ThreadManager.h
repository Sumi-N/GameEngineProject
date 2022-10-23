#pragma once
#include "Define.h"

namespace Tempest
{
	class ThreadManager
	{
	public:
		static uint8_t RegisterThread();

		static void SyncPoint1(uint8_t thread_id);
		static void SyncPoint2(uint8_t thread_id);
	};
}