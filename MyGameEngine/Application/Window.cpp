#include "Window.h"

void Window::BindEvent()
{
	SetEventCallback(std::bind(&Window::OnEvent, this, std::placeholders::_1));
}

void Window::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Window::OnWindowClose, this, std::placeholders::_1));
	dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Window::OnWindowResize, this, std::placeholders::_1));
}

bool Window::OnWindowClose(WindowCloseEvent& e)
{
	DEBUG_PRINT("Need to close the engine");
	return true;
}

bool Window::OnWindowResize(WindowResizeEvent& e)
{
	DEBUG_PRINT("Need to resize the renderer");
	return true;
}

