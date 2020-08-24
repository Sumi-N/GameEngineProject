#include "Window.h"

#ifdef ENGINE_PLATFORM_WINDOWS

void Window::Init(const WindowProperty& property)
{
	data.title = property.title;
	data.width = property.width;
	data.height = property.height;

	if (glfwInit() == GL_FALSE)
	{
		DEBUG_PRINT("Cannot initialize GLFW");
		return;
	}

	atexit(glfwTerminate);

	//Select OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating a window
	glfwwindow = glfwCreateWindow(data.width, data.height, data.title.c_str(), NULL, NULL);

	if (!glfwwindow)
	{
		// If the window is not created
		DEBUG_PRINT("Cannot create GLFW window");
		glfwTerminate();
		return;
	}

	// Attached the OpenGL to this window
	glfwMakeContextCurrent(glfwwindow);

	// Set V-Sync
	glfwSwapInterval(1);
}

bool Window::CheckShutdown()
{
	if (glfwWindowShouldClose(glfwwindow) == GL_TRUE)
		return false;

	glfwPollEvents();

	return true;
}

void Window::SwapBuffer()
{
	glfwSwapBuffers(glfwwindow);
}

void Window::Shutdown()
{
	glfwDestroyWindow(glfwwindow);
	glfwTerminate();
}

HWND Window::GetNaitiveWindowsHandler()
{
	return glfwGetWin32Window(glfwwindow);
}

#endif // ENGINE_PLATFORM_WINDOWS

