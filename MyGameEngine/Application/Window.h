#pragma once
#include "Define.h"

struct WindowProperty
{
	std::string title;
	unsigned int width;
	unsigned int height;

	WindowProperty(const std::string& i_title = "Tempest Engine") 
		: title(i_title), width(SCREEN_WIDTH), height(SCREEN_HEIGHT){};
};

class Window
{
public:
	Window(){};
	~Window(){};

	#ifdef  ENGINE_PLATFORM_WINDOWS
	#include "Window.win.h"
	#endif //  ENGINE_PLATFORM_WINDOWS
};