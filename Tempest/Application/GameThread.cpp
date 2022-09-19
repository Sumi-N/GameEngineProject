#include "GameThread.h"


namespace Tempest
{
	HWND WindowsHanlder;
	Time GameThreadTime;

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
		UserInput.GetWindowsHandler(WindowsHanlder);
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
		Time::Update(GameThreadTime);
		Entity::Update(static_cast<float>(GameThreadTime.dt));
	}

	void GameThread::CriticalSection()
	{
	}

	void GameThread::CleanUp()
	{
	}
}