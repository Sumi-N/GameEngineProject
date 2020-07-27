#pragma once

#include "Define.h"
#include "Thread.h"
#include "GameThread.h"

class RenderThread : public Thread
{
public:
	void Boot() override;
	void Init() override;
	void Run() override;
	void Refresh();
	void CleanUp() override;
	void PassDataTo(Thread *) override;
};

inline void RenderThread::Boot()
{
	Graphic::Boot();
}

inline void RenderThread::Init()
{
	// Init scene entity
	SceneEntity::Init();
	Graphic::Init();

	Graphic::PreCompute();
}

inline void RenderThread::Run()
{
	bool brunning = true;

	while (brunning)
	{
		// Critical Section
		{
			std::lock_guard<std::mutex> lock_guard(Mutex_Render);

			{
				std::swap(data_game_own, data_render_own);
			}

			b_render_ready = true;
			Condition_Render.notify_one();
		}

		if (!Graphic::PreUpdate())
		{
			brunning = false;
		}

		Graphic::Update(data_render_own);

		Graphic::PostUpdate(data_render_own);
	}

	CleanUp();
}

inline void RenderThread::CleanUp()
{
	Graphic::CleanUp();
}

inline void RenderThread::PassDataTo(Thread * i_thread)
{

}