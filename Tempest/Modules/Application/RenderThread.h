#pragma once

#include "Define.h"
#include "GameThread.h"

namespace Tempest
{
	extern Window* ApplicationWindow;

	class RenderThread : public Thread
	{
	public:
		RenderThread()  = default;
		~RenderThread() = default;

		virtual void Boot() override;
		virtual void Init() override;
		void Reset();
		virtual void CriticalSection() override;
		virtual void NonCriticalSection() override;
		virtual void CleanUp() override;

	private:
		void BindEvent();
		void OnEvent(Event& i_event);
		bool OnWindowClose(WindowCloseEvent i_event);
		bool OnWindowResize(WindowResizeEvent i_event);
	};
}