#pragma once
#include <functional>

#include <Input/ApplicationEvent.h>
#include <Input/KeyEvent.h>
#include <Input/MouseEvent.h>

#include "Define.h"

namespace Tempest
{
	struct WindowProperty
	{
		std::string  title;
		unsigned int width;
		unsigned int height;

		enum GraphicsApiType
		{
			OpenGL,
			Vulkan,
			Size,
		} graphics_type;

		WindowProperty(const std::string& i_title = "Tempest Engine")
			: title(i_title), width(Graphics::InitialScreenWidth), height(Graphics::InitialScreenHeight), graphics_type(GraphicsApiType::Vulkan)
		{};
	};

	class Window
	{
	public:
		Window() = default;
		~Window() = default;

	public:

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		struct WindowData
		{
			std::string  title;
			unsigned int width;
			unsigned int height;
			bool         VSync;

			std::function<void(Event&)> eventcallback;

			WindowData() : title("Empty"), width(0), height(0), VSync(false) {};
		} data;

#ifdef  ENGINE_PLATFORM_WINDOWS
#include "Window.win.h"
#endif //  ENGINE_PLATFORM_WINDOWS
	};
}