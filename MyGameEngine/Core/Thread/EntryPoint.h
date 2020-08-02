#pragma once

#include "Define.h"
#include "Thread.h"
#include "GameThread.h"
#include "RenderThread.h"

namespace System
{
	void RunGameThread()
	{
		Thread_Game.Run();
	}

	void RunRenderThread()
	{
		Thread_Render.Run();
	}

	void BootRenderThread()
	{
		// Start boot process for render thread
		{
			std::lock_guard<std::mutex> lock_guard(Thread::Mutex_Render);
			Thread_Render.Boot();
			Thread::b_render_ready = true;
			Thread::Condition_Render.notify_one();
		}
		// Wait until both game and render thread finish boot process
		{
			std::unique_lock<std::mutex> unique_lock_guard(Thread::Mutex_Game);
			while (!Thread::b_game_ready)
				Thread::Condition_Game.wait(unique_lock_guard);
		}
		// Start init process for render thread
		{
			std::lock_guard<std::mutex> lock_guard(Thread::Mutex_Render);
			Thread_Render.Init();
			Thread::b_render_ready = true;
			Thread::Condition_Render.notify_one();
		}
		// Wait until both game and render thread finish initializing
		{
			std::unique_lock<std::mutex> unique_lock_guard(Thread::Mutex_Game);
			while (!Thread::b_game_ready)
				Thread::Condition_Game.wait(unique_lock_guard);
			Thread::b_game_ready = false;
		}
	}

	void BootGameThread()
	{
		// Start boot process for game thread
		{
			std::lock_guard<std::mutex> lock_guard(Thread::Mutex_Game);
			Thread_Game.Boot();
			Thread::b_game_ready = true;
			Thread::Condition_Game.notify_one();
		}
		// Wait until both game and render thread finish boot process
		{
			std::unique_lock<std::mutex> unique_lock_guard(Thread::Mutex_Render);
			while (!Thread::b_render_ready)
				Thread::Condition_Render.wait(unique_lock_guard);
		}
		// Start init process for game thread
		{
			std::lock_guard<std::mutex> lock_guard(Thread::Mutex_Game);
			Thread_Game.Init();
			Thread::b_game_ready = true;
			Thread::Condition_Game.notify_one();
		}
		// Wait until both game and render thread finish initializing
		{
			std::unique_lock<std::mutex> unique_lock_guard(Thread::Mutex_Render);
			while (!Thread::b_render_ready)
				Thread::Condition_Render.wait(unique_lock_guard);
			Thread::b_render_ready = false;
		}

		RunGameThread();
	}

	void Boot()
	{
		Thread::b_game_ready = false;
		Thread::b_render_ready = false;

		std::thread gamethread(BootGameThread);
		gamethread.detach();

		BootRenderThread();

		return;
	}

	void Start()
	{
		RunRenderThread();
	}
}