#pragma once
#include <future>
#include <thread>
#include <utility>

#include "Define.h"
#include "ThreadManager.h"

namespace Tempest
{
	class Thread
	{
	public:
		Thread() :is_alive(true), id(255) {}
		~Thread() = default;


		template<typename Callable, typename ... Args>
		void Create(Callable&& function, Args&& ... args)
		{
			id = ThreadManager::RegisterThread();
			future = value.get_future();
			std::thread t([=]
						  {
							  value.set_value_at_thread_exit(0);
							  function(args...);
						  });
			t.detach();
		}

		void WaitThreadFinish() { future.wait(); }

		virtual void Boot();
		virtual void Init();
		virtual void Run();
		virtual void CleanUp();

	protected:

		virtual void CriticalSection();
		virtual void NonCriticalSection();

	public:
		bool is_alive;
		uint8_t id;

	private:
		std::promise<int> value;
		std::future<int> future;
	};
}