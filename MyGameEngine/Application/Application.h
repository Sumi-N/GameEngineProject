#pragma once

#include "Define.h"

class Application
{
public:
	Application(){};
	virtual ~Application(){};
};

static Application* Create();