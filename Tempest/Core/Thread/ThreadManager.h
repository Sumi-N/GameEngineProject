#pragma once
#include "Define.h"

class ThreadManager
{
public:
	static uint8_t RegisterThread(std::mutex&, std::condition_variable&, bool&);
	static uint8_t GetOtherThreadID(const uint8_t&);

	static std::vector<std::mutex*> Mutexs;
	static std::vector<std::condition_variable*> Conditions;
	static std::vector<bool*> b_thread_ready;

private:
	static uint8_t ThreadCounter;
};