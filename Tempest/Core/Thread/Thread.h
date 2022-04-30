#pragma once

#include "Define.h"
#include "ThreadManager.h"

namespace Tempest
{
	class Thread
	{
	public:
		Thread() :brunning(true), thread_id(255) {}
		~Thread() = default;

		void Create();
		virtual void Boot();
		virtual void Init();
		virtual void Run();
		virtual void CleanUp();

		bool brunning;
		uint8_t thread_id;

	protected:
		virtual void CriticalSection();
		virtual void NonCriticalSection();
	};
}