#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>

class Thread
{
	static std::mutex MutexGame;
	static std::mutex MutexRender;
	static std::condition_variable ConditionGame;
	static std::condition_variable ConditionRender;
	static bool brenderready;
	static bool bgameready;

	void Init();
	void Run();
	void PassData(Thread);
};

