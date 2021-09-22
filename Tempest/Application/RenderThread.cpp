#include "RenderThread.h"

namespace Tempest
{

	//Data required for render thread
	GraphicRequiredData  ContainerRenderData[2];
	GraphicRequiredData* ContainerGameOwn = &ContainerRenderData[0];
	GraphicRequiredData* ContainerRenderOwn = &ContainerRenderData[1];

	extern HWND WindowsHanlder;

	void RenderThread::Boot()
	{
		// Create window and init glfw
		window = new Window();
		WindowProperty property;
		window->Init(property);

		WindowsHanlder = window->GetNaitiveWindowsHandler();
		
		LayerStack::Boot();

		// Bind event callbacks including the callbacks that are in imgui layer and other layers 
		BindEvent();

		// Initialize OpenGL
		Graphic::Boot();
	}

	void RenderThread::Init()
	{
		// Init scene entity
		SceneEntity::Init();
		Graphic::Init(window->data.width, window->data.height);
		Graphic::PreCompute();
	}

	void RenderThread::CriticalSection()
	{
		std::swap(ContainerGameOwn, ContainerRenderOwn);
		bready = true;
	}

	void RenderThread::NonCriticalSection()
	{
		if (!window->CheckShutdown())
		{
			brunning = false;
		}

		Graphic::PreUpdate();

		Graphic::Update(ContainerRenderOwn);

		LayerStack::Update();

		Graphic::PostUpdate(ContainerRenderOwn);				

		window->SwapBuffer();
	}

	void RenderThread::SecondCriticalSection()
	{
	}

	void RenderThread::FollowupSection()
	{
		bready = false;
	}

	//inline void RenderThread::Run()
	//{
	//	bool brunning = true;
	//
	//	while (brunning)
	//	{
	//
	//		// Reading this comment section along with GameThread.h is recommended
	//		// The purpose for this section is to swap data between game thread and render thread while the game thread is waiting
	//		{
	//			// 1. The purpose for lock_guard_render is to not let the game thread to touch both the swapping data and b_render_ready variable
	//			// Especially the game thread is constantly referencing b_render_ready variable so it is important to lock the variable when this thread make a change to it
	//			std::lock_guard<std::mutex> lock_guard_render(Mutex_Render);
	//
	//			{
	//				std::swap(data_game_own, data_render_own);
	//			}
	//
	//			// 3. Make b_render_ready true so that it goes through while loop in the game thread 
	//			b_render_ready = true;
	//			// 4. Notify unique_lock_guard_render mutex to release the lock
	//			Condition_Render.notify_one();
	//		}
	//
	//		{
	//			if (!Graphic::PreUpdate())
	//			{
	//				brunning = false;
	//			}
	//
	//			Graphic::Update(data_render_own);
	//
	//			Graphic::PostUpdate(data_render_own);
	//		}
	//
	//		// Almost the same logic as the section below. see the comments below.
	//		{
	//			std::unique_lock<std::mutex> unique_lock_guard_game(Mutex_Game);
	//
	//			while (!b_game_ready)
	//			{
	//				Condition_Game.wait(unique_lock_guard_game);
	//			}
	//		}
	//
	//		b_render_ready = false;
	//	}
	//
	//	CleanUp();
	//}

	void RenderThread::CleanUp()
	{
		LayerStack::CleanUp();
		Graphic::CleanUp();
		window->Shutdown();
		delete window;
	}

	void RenderThread::BindEvent()
	{
		window->data.eventcallback = std::bind(&RenderThread::OnEvent, this, std::placeholders::_1);
	}

	void RenderThread::OnEvent(Event& i_event)
	{
		EventDispatcher dispatcher(i_event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&RenderThread::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&RenderThread::OnWindowResize, this, std::placeholders::_1));

		LayerStack::OnEvent(i_event);
	}

	bool RenderThread::OnWindowClose(WindowCloseEvent i_event)
	{
		window->OnWindowClose(i_event);
		return true;
	}

	bool RenderThread::OnWindowResize(WindowResizeEvent i_event)
	{
		Graphic::ChangeViewPortSize(window->data.width, window->data.height);
		window->OnWindowResize(i_event);
		return true;
	}

}