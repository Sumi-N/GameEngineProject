#pragma once

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

}

inline void RenderThread::Run()
{
	while (true)
	{

	}
}

inline void RenderThread::CleanUp()
{

}

inline void RenderThread::PassDataTo(Thread i_thread)
{

}