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
		void Boot() override;
		void Init() override;
		void CriticalSection() override;
		void NonCriticalSection() override;
		void SecondCriticalSection() override;
		void FollowupSection() override;
		void CleanUp() override;

		// For key call backs setting
	private:
		void BindEvent();
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent e);
		bool OnWindowResize(WindowResizeEvent e);

	private:
		LayerStack layerstack;
	};
}