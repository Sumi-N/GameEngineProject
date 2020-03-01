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


		{
			std::unique_lock<std::mutex> unique_lock_guard(Mutex_Render);
			while (!b_render_ready)
				Condition_Render.wait(unique_lock_guard);
			{

			}
			b_render_ready = false;
		}
	}
}

inline void GameThread::CleanUp()
{

}

inline void GameThread::PassDataTo(Thread i_thread)
{

}