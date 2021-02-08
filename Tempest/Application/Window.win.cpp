#include "Window.h"

#ifdef ENGINE_PLATFORM_WINDOWS

namespace Tempest
{

	void Window::SetVSync(bool i_enable)
	{
		if (i_enable)
		{
			data.VSync = true;
			glfwSwapInterval(1);
		}
		else
		{
			data.VSync = false;
			glfwSwapInterval(0);
		}
	}

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
		SetVSync(true);

		// Set event callbacks
		glfwSetWindowUserPointer(glfwwindow, &data);

		glfwSetWindowSizeCallback(glfwwindow, [](GLFWwindow* i_window, int i_width, int i_height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(i_window);
			data.width = i_width;
			data.height = i_height;

			WindowResizeEvent event(i_width, i_height);
			data.eventcallback(event);
		});

		glfwSetWindowCloseCallback(glfwwindow, [](GLFWwindow* i_window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(i_window);

			WindowCloseEvent event;
			data.eventcallback(event);
		});

		glfwSetKeyCallback(glfwwindow, [](GLFWwindow* i_window, int i_key, int i_scancode, int i_action, int i_mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(i_window);

			switch (i_action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(static_cast<VirtualKey>(i_key), 0);
				data.eventcallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(static_cast<VirtualKey>(i_key));
				data.eventcallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(static_cast<VirtualKey>(i_key), 1);
				data.eventcallback(event);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(glfwwindow, [](GLFWwindow* i_window, int i_button, int i_action, int i_mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(i_window);

			switch (i_action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(static_cast<VirtualKey>(i_button));
				data.eventcallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(static_cast<VirtualKey>(i_button));
				data.eventcallback(event);
				break;
			}
			}
		});

		glfwSetCursorPosCallback(glfwwindow, [](GLFWwindow* i_window, double i_xpos, double i_ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(i_window);

			MouseMovedEvent event(static_cast<float>(i_xpos), static_cast<float>(i_ypos));
			data.eventcallback(event);
		});

		// Initialize GLEW
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			DEBUG_PRINT("Cannot initialize GLEW");
			return;
		}
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

}

#endif // ENGINE_PLATFORM_WINDOWS

