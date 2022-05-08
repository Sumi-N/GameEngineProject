#include "Application.h"

namespace Tempest
{

	GameThread Thread_Game;
	RenderThread Thread_Render;
	Window* window;

	void Application::Invoke()
	{
		Thread_Game.Create();
		Thread_Render.Create();

		std::thread gamethread(InvokeGameThread);
		gamethread.detach();

		InvokeRenderThread();

		return;
	}

	void Application::Run()
	{
		// Run render thread
		RunRenderThread();
	}

	void Application::InvokeRenderThread()
	{
		// Start boot process for render thread
		{			
			Thread_Render.Boot();			
			ThreadManager::SyncPoint1(Thread_Render.thread_id);
		}
		// Wait until both game and render thread finish boot process		
		// Start init process for render thread
		{			
			Thread_Render.Init();
			ThreadManager::SyncPoint2(Thread_Render.thread_id);			
		}
		// Wait until both game and render thread finish init process
	}

	void Application::InvokeGameThread()
	{
		// Start boot process for game thread
		{			
			Thread_Game.Boot();
			ThreadManager::SyncPoint1(Thread_Game.thread_id);
		}
		// Wait until both game and render thread finish boot process	
		// Start init process for game thread
		{			
			Thread_Game.Init();
			ThreadManager::SyncPoint2(Thread_Game.thread_id);			
		}
		// Wait until both game and render thread finish init process

		RunGameThread();
	}

	void Application::RunGameThread()
	{
		Thread_Game.Run();
	}

	void Application::RunRenderThread()
	{
		Thread_Render.Run();
	}

}