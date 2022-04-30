#include "GameThread.h"


namespace Tempest
{	
	HWND WindowsHanlder;
	Time GameThreadTime;	

	void GameThread::Boot()
	{
		Entity::Boot();
	}

	void GameThread::Init()
	{
		Time::Init();
		Entity::Init();
		EntityCopy::Init();
		UserInput.Init();		

#ifdef ENGINE_PLATFORM_WINDOWS
		UserInput.GetWindowsHandler(WindowsHanlder);
#endif // ENGINE_PLATFORM_WINDOWS

	}

	void GameThread::NonCriticalSection()
	{		
		UserInput.Populate();
		Time::Update(GameThreadTime);		
		Entity::Update(static_cast<float>(GameThreadTime.dt));						
	}

	void GameThread::CriticalSection()
	{
		WriteDataToOwningThread();				
	}

	void GameThread::CleanUp()
	{		
	}

	void GameThread::WriteDataToOwningThread()
	{
	}
}