#include "Thread.h"

void Thread::Create()
{
	thread_id = ThreadManager::RegisterThread(mutex, condition, bready);
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

			SecondCriticalSection();
		}

		FollowupSection();
	}

	CleanUp();
}

void Thread::CleanUp()
{

}

void Thread::Eject()
{
}

void Thread::CriticalSection()
{

}

void Thread::NonCriticalSection()
{

}

void Thread::SecondCriticalSection()
{

}

void Thread::FollowupSection()
{

}
