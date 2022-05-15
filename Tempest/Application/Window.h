#pragma once
#include "Define.h"

namespace Tempest
{

	struct WindowProperty
	{
		std::string  title;
		unsigned int width;
		unsigned int height;

		WindowProperty(const std::string& i_title = "Tempest Engine")
			: title(i_title), width(ScreenWidth), height(ScreenHeight)
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