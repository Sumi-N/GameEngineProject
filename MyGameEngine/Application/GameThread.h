#pragma once

#include "Define.h"
#include "RenderThread.h"

class GameThread : public Thread
{
public:
	void Boot() override;
	void Init() override;
	void CriticalSection() override;
	void NonCriticalSection() override;
	void CriticalSectionOther() override;
	void FollowupSection() override;
	void CleanUp() override;

	void WriteDataToOwningThread();
};

