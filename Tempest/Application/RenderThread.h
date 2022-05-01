#pragma once

#include "Define.h"
#include "GameThread.h"
#include "Window.h"

namespace Tempest
{
	extern Window* window;

	class RenderThread : public Thread
	{
	public:
		RenderThread()  = default;
		~RenderThread() = default;

		void Boot() override;
		void Init() override;
		void CriticalSection() override;
		void NonCriticalSection() override;		
		void CleanUp() override;		

	private:
		void BindEvent();
		void OnEvent(Event& i_event);
		bool OnWindowClose(WindowCloseEvent i_event);
		bool OnWindowResize(WindowResizeEvent i_event);
	};
}