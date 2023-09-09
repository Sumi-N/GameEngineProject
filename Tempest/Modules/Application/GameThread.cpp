#include "GameThread.h"


namespace Tempest
{
	HWND g_WindowsHanlder;
	Time g_GameThreadTime;

	Delegate<> GameThreadOnReset;

	void GameThread::Boot()
	{
		Entity::Boot();

		GameThreadOnReset = Delegate<>::Create<GameThread, &GameThread::Reset>(this);
	}

	void GameThread::Init()
	{
		Time::Init();
		UserInput.Init();
		Entity::Init();

#ifdef ENGINE_PLATFORM_WINDOWS
		UserInput.GetWindowsHandler(g_WindowsHanlder);
#endif // ENGINE_PLATFORM_WINDOWS
	}

	void GameThread::Reset()
	{
		Entity::Boot();
		Entity::Init();
	}

	void GameThread::NonCriticalSection()
	{
		UserInput.Populate();
		Time::Update(g_GameThreadTime);
		Entity::Update(static_cast<float>(g_GameThreadTime.dt));
	}

	void GameThread::CriticalSection()
	{
	}

	void GameThread::CleanUp()
	{
	}
}