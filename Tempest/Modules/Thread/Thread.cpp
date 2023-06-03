#include "Thread.h"
#include <Time/Time.h>

namespace Tempest
{
	void Thread::Boot() {}

	void Thread::Init() {}

	void Thread::Run()
	{
		while (is_alive)
		{
			{
				NonCriticalSection();
			}

			ThreadManager::SyncPoint1(id);

			{
				CriticalSection();
			}

			ThreadManager::SyncPoint2(id);
		}

		CleanUp();
	}

	void Thread::CleanUp() {}

	void Thread::CriticalSection() {}

	void Thread::NonCriticalSection() {}
}