#pragma once
#include "Define.h"
#include "ThreadManager.h"

namespace Tempest
{
	class Thread
	{
	public:
		Thread() :brunning(true), bready(false), thread_id(255) {}
		~Thread() = default;

		void Create();
		virtual void Boot();
		virtual void Init();
		virtual void Run();
		virtual void CleanUp();
		virtual void Eject();

		bool bready;
		std::mutex mutex;
		std::condition_variable condition;

	protected:

		bool brunning;
		uint8_t thread_id;

		virtual void CriticalSection();
		virtual void NonCriticalSection();
		virtual void SecondCriticalSection();
		virtual void FollowupSection();
	};
}