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
	void CriticalSectionOther() override;
	void FollowupSection() override;
	void CleanUp() override;
};