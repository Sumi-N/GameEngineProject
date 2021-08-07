#pragma once
#include "ThreadManager.h"

namespace Tempest
{
	Array<std::mutex*>              ThreadManager::Mutexs;
	Array<std::condition_variable*> ThreadManager::Conditions;
	Array<bool*>                    ThreadManager::b_thread_ready;
	uint8_t                               ThreadManager::ThreadCounter = 0;


	uint8_t ThreadManager::RegisterThread(std::mutex& i_mutex, std::condition_variable& i_condition, bool& i_bool)
	{
		Mutexs.push_back(&i_mutex);
		Conditions.push_back(&i_condition);
		b_thread_ready.push_back(&i_bool);

		return ThreadCounter++;
	}

	uint8_t ThreadManager::GetOtherThreadID(const uint8_t& i_thread_id)
	{
		return i_thread_id == 0 ? 1 : 0;
	}
}