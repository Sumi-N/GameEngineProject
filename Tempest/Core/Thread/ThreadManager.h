#pragma once
#include "Define.h"

namespace Tempest
{
	class ThreadManager
	{
	public:
		static uint8_t RegisterThread(std::mutex&, std::condition_variable&, bool&);
		static uint8_t GetOtherThreadID(const uint8_t&);

		static Array<std::mutex*> Mutexs;
		static Array<std::condition_variable*> Conditions;
		static Array<bool*> b_thread_ready;

	private:
		static uint8_t ThreadCounter;
	};
}