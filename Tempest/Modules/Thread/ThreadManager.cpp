﻿#pragma once
#include "ThreadManager.h"
#include "Thread.h"

namespace Tempest
{
	uint8_t ThreadCount{0};
	Thread* Threads[s_MaxThreadCount];

	uint8_t ThreadManager::RegisterThread(Thread* p_thread)
	{
		Threads[ThreadCount] = p_thread;
		uint8_t ret_id = ThreadCount;
		ThreadCount++;
		DEBUG_ASSERT(ThreadCount <= s_MaxThreadCount);
		return ret_id;
	}

	void ThreadManager::PropagateEndSignal()
	{
		for (int i = 0; i < ThreadCount; i++)
		{
			Threads[i]->is_alive = false;
		}
	}

	// TODO RegisterThred で導入した数の　Thread　しか SyncPoint で待てない。
	// 将来的に3つ以上のスレッドが動作した時の、どのスレッドとどのスレッドが同期するのか等を指定できるようにする
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