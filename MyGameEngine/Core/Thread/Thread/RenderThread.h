#pragma once

#include "Thread.h"

class RenderThread : public Thread
{
public:
	void Init() override;
	void Run() override;
	void PassDataTo(Thread) override;
};