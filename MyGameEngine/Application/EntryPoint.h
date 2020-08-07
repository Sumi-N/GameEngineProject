#pragma once

#include "Define.h"
#include "GameThread.h"
#include "RenderThread.h"

namespace System
{
	// Forward declaration
	void BootRenderThread();
	void BootGameThread();
	void RunRenderThread();
	void RunGameThread();

	void Boot()
	{
		Thread_Game.Create();
		Thread_Render.Create();

		std::thread gamethread(BootGameThread);
		gamethread.detach();

		BootRenderThread();

		return;
	}

	void Start()
	{
		RunRenderThread();
	}

	void BootRenderThread()
	{
		// Start boot process for render thread
		{
			std::lock_guard<std::mutex> lock_guard(Thread_Render.mutex);
			Thread_Render.Boot();
			Thread_Render.bready = true;
			Thread_Render.condition.notify_one();
		}
		// Wait until both game and render thread finish boot process
		{
			std::unique_lock<std::mutex> unique_lock_guard(Thread_Game.mutex);
			while (!Thread_Game.bready)
				Thread_Game.condition.wait(unique_lock_guard);
		}
		// Start init process for render thread
		{
			std::lock_guard<std::mutex> lock_guard(Thread_Render.mutex);
			Thread_Render.Init();
			Thread_Render.bready = true;
			Thread_Render.condition.notify_one();
		}
		// Wait until both game and render thread finish initializing
		{
			std::unique_lock<std::mutex> unique_lock_guard(Thread_Game.mutex);
			while (!Thread_Game.bready)
				Thread_Game.condition.wait(unique_lock_guard);
		}
	}

	void BootGameThread()
	{
		// Start boot process for game thread
		{
			std::lock_guard<std::mutex> lock_guard(Thread_Game.mutex);
			Thread_Game.Boot();
			Thread_Game.bready = true;
			Thread_Game.condition.notify_one();
		}
		// Wait until both game and render thread finish boot process
		{
			std::unique_lock<std::mutex> unique_lock_guard(Thread_Render.mutex);
			while (!Thread_Render.bready)
				Thread_Render.condition.wait(unique_lock_guard);
		}
		// Start init process for game thread
		{
			std::lock_guard<std::mutex> lock_guard(Thread_Game.mutex);
			Thread_Game.Init();
			Thread_Game.bready = true;
			Thread_Game.condition.notify_one();
		}
		// Wait until both game and render thread finish initializing
		{
			std::unique_lock<std::mutex> unique_lock_guard(Thread_Render.mutex);
			while (!Thread_Render.bready)
				Thread_Render.condition.wait(unique_lock_guard);
			Thread_Render.bready = false;
		}

		RunGameThread();
	}

	void RunGameThread()
	{
		Thread_Game.Run();
	}

	void RunRenderThread()
	{
		Thread_Render.Run();
	}
}