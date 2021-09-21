#pragma once

#include "Define.h"
#include "GameThread.h"
#include "RenderThread.h"
#include "Window.h"

namespace Tempest
{

	class Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

	protected:
		void Execute();

	private:
		static void Boot();
		static void Start();
		static void BootRenderThread();
		static void BootGameThread();
		static void RunGameThread();
		static void RunRenderThread();
	};

	inline void Application::Execute()
	{
		Application::Boot();
		Application::Start();
	}

	static Application* Create();

}