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
	void CleanUp() override;
	void WriteDataToOwningThread() override;
};

inline void RenderThread::Boot()
{
	Graphic::Boot();
	WindowsHanlder = Graphic::GetWindowsHandler();
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
		// Almost the same logic as the section below. see the comments below.
		{
			std::unique_lock<std::mutex> unique_lock_guard_game(Mutex_Game);

			while (!b_game_ready)
			{
				Condition_Game.wait(unique_lock_guard_game);
			}
		}

		// Reading this comment section along with GameThread.h is recommended
		// The purpose for this section is to swap data between game thread and render thread while the game thread is waiting
		{
			// 1. The purpose for lock_guard_render is to not let the game thread to touch both the swapping data and b_render_ready variable
			// Especially the game thread is constantly referencing b_render_ready variable so it is important to lock the variable when this thread make a change to it
			std::lock_guard<std::mutex> lock_guard_render(Mutex_Render);

			{
				std::swap(data_game_own, data_render_own);
			}

			// 3. Make b_render_ready true so that it goes through while loop in the game thread 
			b_render_ready = true;
			// 4. Notify unique_lock_guard_render mutex to release the lock
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

inline void RenderThread::WriteDataToOwningThread()
{

}