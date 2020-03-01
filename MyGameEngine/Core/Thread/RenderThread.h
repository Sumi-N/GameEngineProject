#pragma once

#include <Graphics/Graphics/Graphic.h>

#include "Thread.h"

class RenderThread : public Thread
{
public:
	void Init() override;
	void Run() override;
	void CleanUp() override;
	void PassDataTo(Thread) override;
};

inline void RenderThread::Init()
{
	Graphic::Init();
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

	}
}

inline void RenderThread::CleanUp()
{

}

inline void RenderThread::PassDataTo(Thread i_thread)
{

}