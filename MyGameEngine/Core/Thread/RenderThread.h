#pragma once

#include "Define.h"
#include "Thread.h"

class RenderThread : public Thread
{
public:
	void Boot() override;
	void Init() override;
	void Run() override;
	void CleanUp() override;
	void PassDataTo(Thread) override;
};

inline void RenderThread::Boot()
{
	Graphic::Init();
}


inline void RenderThread::Init()
{
	
}

inline void RenderThread::Run()
{
	while (true)
	{
		// Critical Section
		{
			std::lock_guard<std::mutex> lock_guard(Mutex_Render);

			{
			
				
			}

			b_render_ready = true;
			Condition_Render.notify_one();
		}

		Graphic::Update();
	}
}

inline void RenderThread::CleanUp()
{

}

inline void RenderThread::PassDataTo(Thread i_thread)
{

}