#pragma once
#include "Event.h"

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(unsigned int i_width, unsigned int i_height) : width(i_width), height(i_height){};
	
	EVENT_CLASS_MACRO(WindowResize, WindowEvent)

private:
	unsigned int width, height;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;

	EVENT_CLASS_MACRO(WindowClose, WindowEvent)
};