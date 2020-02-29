#pragma once

#include <Core/Time/Time.h>

#include "Thread.h"

class GameThread : public Thread
{
public:
	void Init() override;
	void Run() override;
	void CleanUp() override;
	void PassDataTo(Thread) override;
};

inline void GameThread::Init()
{
	Time::Init();
}

inline void GameThread::Run()
{
	while (true)
	{

	}
}

inline void GameThread::CleanUp()
{

}

inline void GameThread::PassDataTo(Thread i_thread)
{

}