#include "Window.h"

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

