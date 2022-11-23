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

		auto glfw_init_result = glfwInit();
		DEBUG_ASSERT_WITHMESSAGE(glfw_init_result == GL_TRUE, "Cannot initialize glfw");

		atexit(glfwTerminate);

		//Select OpenGL Version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

		switch (property.graphics_type)
		{
		case WindowProperty::GraphicsApiType::Vulkan:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			break;
		case WindowProperty::GraphicsApiType::OpenGL:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			break;
		default:
			break;
		}

		// Creating a window
		glfwwindow = glfwCreateWindow(data.width, data.height, data.title.c_str(), NULL, NULL);

		if (!glfwwindow)
		{
			glfwTerminate();
			DEBUG_ASSERT_WITHMESSAGE(false, "Cannot create GLFW window");
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
			if (!data.eventcallback)
			{
				return;
			}

			WindowResizeEvent event(i_width, i_height);
			data.eventcallback(event);
		});

		glfwSetWindowCloseCallback(glfwwindow, [](GLFWwindow* i_window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(i_window);
			if (!data.eventcallback)
			{
				return;
			}

			WindowCloseEvent event;
			data.eventcallback(event);
		});

		glfwSetKeyCallback(glfwwindow, [](GLFWwindow* i_window, int i_key, int i_scancode, int i_action, int i_mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(i_window);
			if (!data.eventcallback)
			{
				return;
			}

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
			if (!data.eventcallback)
			{
				return;
			}

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
			if (!data.eventcallback)
			{
				return;
			}
			MouseMovedEvent event(static_cast<float>(i_xpos), static_cast<float>(i_ypos));
			data.eventcallback(event);
		});
	}

	bool Window::CheckShutdown()
	{
		if (glfwWindowShouldClose(glfwwindow) == GL_TRUE)
			return false;

		glfwPollEvents();

		return true;
	}

	void Window::SetContext()
	{
		glfwMakeContextCurrent(glfwwindow);
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

	GLFWwindow* Window::GetGLFWWindow()
	{
		return glfwwindow;
	}

	Array<const char*> Window::GetRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for (size_t i = 0; i < glfwExtensionCount; i++)
		{
			extensions.PushBack(glfwExtensions[i]);
		}

#ifdef ENABLE_VULKAN_VALIDATION_LAYERS
		extensions.PushBack("VK_EXT_debug_utils");
#endif

		return extensions;
	}
}

#endif // ENGINE_PLATFORM_WINDOWS

