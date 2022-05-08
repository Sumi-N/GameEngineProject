#include "GameThread.h"


namespace Tempest
{	
	extern GraphicRequiredData GraphicsData;
	HWND WindowsHanlder;
	Time GameThreadTime;

	void WriteDataToOwningThread(GraphicRequiredData*);

	void GameThread::Boot()
	{
		Entity::Boot();
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

	void GameThread::NonCriticalSection()
	{
		UserInput.Populate();
		Time::Update(GameThreadTime);
		Entity::Update(static_cast<float>(GameThreadTime.dt));
	}

	void GameThread::CriticalSection()
	{
		//WriteDataToOwningThread(&GraphicsData);
	}

	void GameThread::CleanUp()
	{
	}
}