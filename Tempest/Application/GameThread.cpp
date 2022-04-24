#include "GameThread.h"


namespace Tempest
{	
	HWND WindowsHanlder;

	void GameThread::Boot()
	{
		Entity::Boot();
	}

	void GameThread::Init()
	{
		Time::Init();
		Entity::Init();
		UserInput.Init();

#ifdef ENGINE_PLATFORM_WINDOWS
		UserInput.GetWindowsHandler(WindowsHanlder);
#endif // ENGINE_PLATFORM_WINDOWS

	}

	void GameThread::CriticalSection()
	{
		bready = false;
		UserInput.Populate();
		Time::Update();
		Entity::Update(static_cast<float>(Time::dt));
		bready = true;
	}

	void GameThread::NonCriticalSection()
	{
	}

	void GameThread::SecondCriticalSection()
	{
		WriteDataToOwningThread();
	}

	void GameThread::FollowupSection()
	{
		*ThreadManager::b_thread_ready[ThreadManager::GetOtherThreadID(thread_id)] = false;
	}

	//inline void GameThread::Run()
	//{
	//	while (true)
	//	{
	//		// Almost the same logic as the section below. see the comments below.
	//		{
	//			std::lock_guard<std::mutex> lock_guard_game(Mutex_Game);
	//
	//			b_game_ready = false;
	//
	//			{
	//				UserInput.Populate();
	//				Time::Update();
	//				Entity::Update(static_cast<float>(Time::dt));
	//			}
	//
	//			b_game_ready = true;
	//			Condition_Game.notify_one();
	//		}
	//
	//		// Reading this comment section along with RenderThread.h is recommended
	//		// The purpose for this section is to wait for the render thread to finish swapping data
	//		{
	//			// 2. unique_lock_guard_render will block the thread until b_render_ready become true
	//			// The reason this is unique_lock is because this lock has to be released from the render thread 
	//			std::unique_lock<std::mutex> unique_lock_guard_render(Mutex_Render);
	//
	//			// 5. Block the logic until the render thread finishing swapping
	//			while (!b_render_ready)
	//			{
	//				Condition_Render.wait(unique_lock_guard_render);
	//			}
	//
	//			{
	//				WriteDataToOwningThread();
	//			}
	//
	//			// 6. After finish writing the data, make b_render_ready true 
	//			// So that the render thread wouldn't render the same scene more than one
	//			b_render_ready = false;
	//		}
	//	}
	//}

	void GameThread::CleanUp()
	{

	}

	void GameThread::WriteDataToOwningThread()
	{
	}
}