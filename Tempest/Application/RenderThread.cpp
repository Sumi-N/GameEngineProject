#include "RenderThread.h"

namespace Tempest
{

	//Data required for render thread
	GraphicRequiredData  container_render[2];
	GraphicRequiredData* data_game_own = &container_render[0];
	GraphicRequiredData* data_render_own = &container_render[1];

	extern HWND WindowsHanlder;

	void RenderThread::Boot()
	{
		// Create window and init glfw
		window = new Window();
		WindowProperty property;
		window->Init(property);

		WindowsHanlder = window->GetNaitiveWindowsHandler();

		// Push imgui layer to layer stack
		ImguiLayer* imgui_layer = new ImguiLayer();
		layerstack.PushLayer(imgui_layer);

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
		std::swap(data_game_own, data_render_own);
		bready = true;
	}

	void RenderThread::NonCriticalSection()
	{
		if (!window->CheckShutdown())
		{
			brunning = false;
		}

		Graphic::PreUpdate();

		Graphic::Update(data_render_own);

		Graphic::PostUpdate(data_render_own);

		// Layer's update
		// The reason this layer is placed here is because we have imgui layer
		// that requires to be updated before swap buffer on OpenGL 
		for (Layer* layer : layerstack.Layers())
		{
			layer->OnUpdate();
		}

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
		layerstack.CleanUp();
		Graphic::CleanUp();
		window->Shutdown();
		delete window;
	}

	void RenderThread::BindEvent()
	{
		window->data.eventcallback = std::bind(&RenderThread::OnEvent, this, std::placeholders::_1);
	}

	void RenderThread::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&RenderThread::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&RenderThread::OnWindowResize, this, std::placeholders::_1));

		for (auto layer : layerstack.Layers())
		{
			layer->OnEvent(e);
		}
	}

	bool RenderThread::OnWindowClose(WindowCloseEvent e)
	{
		window->OnWindowClose(e);
		return true;
	}

	bool RenderThread::OnWindowResize(WindowResizeEvent e)
	{
		Graphic::ChangeViewPortSize(window->data.width, window->data.height);
		window->OnWindowResize(e);
		return true;
	}

}