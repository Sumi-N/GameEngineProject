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
		static void Invoke();
		static void Run();
		static void InvokeRenderThread();
		static void InvokeGameThread();
		static void RunGameThread();
		static void RunRenderThread();
	};

	inline void Application::Execute()
	{
		Application::Invoke();
		Application::Run();
	}

	static Application* Create();

}