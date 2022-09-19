#include "Thread.h"
#include <Time/Time.h>

namespace Tempest
{
	void Thread::Create()
	{
		thread_id = ThreadManager::RegisterThread();
	}

	void Thread::Boot()
	{
	}

	void Thread::Init()
	{
	}

	void Thread::Run()
	{
		while (brunning)
		{
			{
				NonCriticalSection();
			}

			ThreadManager::SyncPoint1(thread_id);

			{
				CriticalSection();
			}

			ThreadManager::SyncPoint2(thread_id);
		}

		CleanUp();
	}

	void Thread::CleanUp()
	{
	}

	void Thread::CriticalSection()
	{
	}

	void Thread::NonCriticalSection()
	{
	}
}