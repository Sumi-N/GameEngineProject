#include "RenderThread.h"

namespace Tempest
{		
	extern HWND WindowsHanlder;	
	GraphicRequiredData  GraphicsData;

	void RenderThread::Boot()
	{
		// Create window and init glfw
		window = new Window();
		WindowProperty property;
		window->Init(property);

		WindowsHanlder = window->GetNaitiveWindowsHandler();

		// Bind event callbacks including the callbacks that are in imgui layer and other layers 
		BindEvent();

		// Initialize OpenGL
		Graphic::Boot();

		LayerStack::Boot();
	}

	void RenderThread::Init()
	{		
		// Init scene Entity
		SceneEntity::Init();

		Graphic::Init(window->data.width, window->data.height);
		
		Graphic::PreCompute();		
	}	

	void RenderThread::NonCriticalSection()
	{		
		if (!window->CheckShutdown())
		{
			brunning = false;
		}		
		
		Graphic::PreUpdate(&GraphicsData);

		Graphic::Update(&GraphicsData);

		LayerStack::Update();

		Graphic::PostUpdate(&GraphicsData);

		window->SwapBuffer();		
	}

	void RenderThread::CriticalSection()
	{				
	}

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