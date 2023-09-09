#pragma once

#include "Define.h"
#include "GameThread.h"
#include "RenderThread.h"

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
		static void InvokeRenderThread();
		static void InvokeGameThread();

	};

	inline void Application::Execute()
	{
		Application::Invoke();
	}

	static Application* Create();
}