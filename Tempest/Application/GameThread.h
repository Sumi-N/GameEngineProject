#pragma once

#include "Define.h"
#include "RenderThread.h"

namespace Tempest
{	
	class GameThread : public Thread
	{
	public:
		virtual void Boot() override;
		virtual void Init() override;
		virtual void Reset();
		void CriticalSection() override;
		virtual void NonCriticalSection() override;		
		virtual void CleanUp() override;		
	};
}

