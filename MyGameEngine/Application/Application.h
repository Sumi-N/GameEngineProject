#pragma once

class Application
{
public:
	Application(){};
	virtual ~Application(){};
};

static Application* Create();