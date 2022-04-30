#pragma once

#include "Define.h"
#include "RenderThread.h"

namespace Tempest
{
	class GameThread : public Thread
	{
	public:
		void Boot() override;
		void Init() override;
		void CriticalSection() override;
		void NonCriticalSection() override;		
		void CleanUp() override;

		void WriteDataToOwningThread();
	};
}

