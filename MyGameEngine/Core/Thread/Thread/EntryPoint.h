#pragma once
#include "Define.h"
#include "Thread.h"

namespace System
{
	void Boot()
	{

		Thread::b_game_ready = false;
		Thread::b_render_ready = false;

		std::thread gamethread(BootGameThread);
		BootRenderThread();

		return;
	}

	void BootRenderThread()
	{
		{
			std::lock_guard<std::mutex> lock_guard(Thread::Mutex_Render);
			Thread_Render.Init();
			Thread::b_render_ready = true;
			Thread::Condition_Game.notify_one();
		}

		{
			std::unique_lock<std::mutex> unique_lock_guard(Thread::Mutex_Game);
			while (!Thread::b_game_ready)
				Thread::Condition_Game.wait(unique_lock_guard);
			Thread::b_game_ready = false;
		}

		Thread_Render.Run();
	}

	void BootGameThread()
	{
		{
			std::unique_lock<std::mutex> unique_lock_guard(Thread::Mutex_Render);
			while (!Thread::b_render_ready)
				Thread::Condition_Render.wait(unique_lock_guard);
			Thread::b_render_ready = false;
		}

		{
			std::lock_guard<std::mutex> lock_guard(Thread::Mutex_Game);
			Thread_Game.Init();
			Thread::b_game_ready = true;
			Thread::Condition_Game.notify_one();
		}

		Thread_Game.Run();
	}
}