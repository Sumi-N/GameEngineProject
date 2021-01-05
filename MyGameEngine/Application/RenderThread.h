#pragma once

#include "Define.h"
#include "GameThread.h"
#include "Window.h"

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

private:
	LayerStack layerstack;
};