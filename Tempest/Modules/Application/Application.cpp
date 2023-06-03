#include "Application.h"

namespace Tempest
{

	GameThread g_GameThread;
	RenderThread g_RenderThread;

	void Application::Invoke()
	{
		g_GameThread.Create(InvokeGameThread);
		g_RenderThread.Create(InvokeRenderThread);

		g_GameThread.WaitThreadFinish();
		g_RenderThread.WaitThreadFinish();

		return;
	}

	void Application::InvokeRenderThread()
	{
		// Start boot process for render thread
		{
			g_RenderThread.Boot();
			ThreadManager::SyncPoint1(g_RenderThread.id);
		}
		// Wait until both game and render thread finish boot process
		// Start init process for render thread
		{
			g_RenderThread.Init();
			ThreadManager::SyncPoint2(g_RenderThread.id);
		}
		// Wait until both game and render thread finish init process

		g_RenderThread.Run();
	}

	void Application::InvokeGameThread()
	{
		// Start boot process for game thread
		{
			g_GameThread.Boot();
			ThreadManager::SyncPoint1(g_GameThread.id);
		}
		// Wait until both game and render thread finish boot process
		// Start init process for game thread
		{
			g_GameThread.Init();
			ThreadManager::SyncPoint2(g_GameThread.id);
		}
		// Wait until both game and render thread finish init process

		g_GameThread.Run();
	}
}