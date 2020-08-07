#pragma once
#include "Define.h"
#include "ThreadManager.h"

class Thread
{
public:
	Thread():brunning(true), bready(false),thread_id(255){}
	void Create();
	virtual void Boot(){};
	virtual void Init(){};
	virtual void Run();
	virtual void CleanUp(){};
	virtual void Eject(){};

	bool bready;
	std::mutex mutex;
	std::condition_variable condition;

protected:

	bool brunning;
	uint8_t thread_id;

	virtual void CriticalSection(){};
	virtual void NonCriticalSection(){};
	virtual void CriticalSectionOther(){};
	virtual void FollowupSection(){};
};

inline void Thread::Create()
{
	thread_id = ThreadManager::RegisterThread(mutex, condition, bready);
}

inline void Thread::Run()
{
	while (brunning)
	{
		{
			std::lock_guard<std::mutex> lock_guard(mutex);

			CriticalSection();

			condition.notify_one();
		}

		{
			NonCriticalSection();
		}

		{
			std::unique_lock<std::mutex> unique_lock_guard(*ThreadManager::Mutexs[ThreadManager::GetOtherThreadID(thread_id)]);

			while (!(*ThreadManager::b_thread_ready[ThreadManager::GetOtherThreadID(thread_id)]))
			{
				ThreadManager::Conditions[ThreadManager::GetOtherThreadID(thread_id)]->wait(unique_lock_guard);
			}

			CriticalSectionOther();
		}

		FollowupSection();
	}

	CleanUp();
}

