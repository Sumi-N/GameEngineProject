#pragma once
#include "ThreadManager.h"

namespace Tempest
{
	uint8_t ThreadCount{ 0 };

	uint8_t ThreadManager::RegisterThread()
	{
		return ThreadCount++;
	}

	void ThreadManager::SyncPoint1(uint8_t thread_id)
	{
		static std::mutex mtx;
		static std::condition_variable condition;
		static Array<bool> thread_ready(ThreadCount);
		static bool ready{ false };

		{
			std::lock_guard lock_guard(mtx);
			ready = false;
			thread_ready[thread_id] = true;

			if (thread_ready[0] && thread_ready[1])
			{
				ready = true;
				condition.notify_all();
			}
		}

		{
			std::unique_lock unique_lock(mtx);
			condition.wait(unique_lock, [&] { return ready; });
			thread_ready[thread_id] = false;
		}
	}

	void ThreadManager::SyncPoint2(uint8_t thread_id)
	{
		static std::mutex mtx;
		static std::condition_variable condition;
		static Array<bool> thread_ready(ThreadCount);
		static bool ready{ false };

		{
			std::lock_guard lock_guard(mtx);
			ready = false;
			thread_ready[thread_id] = true;

			if (thread_ready[0] && thread_ready[1])
			{
				ready = true;
				condition.notify_all();
			}
		}

		{
			std::unique_lock unique_lock(mtx);
			condition.wait(unique_lock, [&] { return ready; });
			thread_ready[thread_id] = false;
		}
	}
}