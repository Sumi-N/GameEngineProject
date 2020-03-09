#pragma once

#include "Define.h"
#include "Thread.h"

class GameThread : public Thread
{
public:
	void Boot() override;
	void Init() override;
	void Run() override;
	void CleanUp() override;
	void Eject() override;

	void PassDataTo(Thread) override;
};

inline void GameThread::Boot()
{
}

inline void GameThread::Init()
{
	Time::Init();
	Entity::Init();
}

inline void GameThread::Run()
{
	while (true)
	{

		Entity::Update(Time::dt);

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

inline void GameThread::Eject()
{

}

inline void GameThread::PassDataTo(Thread i_thread)
{

}