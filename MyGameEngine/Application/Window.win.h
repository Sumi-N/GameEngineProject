#pragma once

public:

	void SetEventCallback(const std::function<void(Event&)>& callback) {data.eventcallback = callback;};
	void SetVSync(bool enable);
	bool isVSync() const;

	void Init(const WindowProperty& property);
	bool CheckShutdown();
	void SwapBuffer();
	void Shutdown();

	HWND GetNaitiveWindowsHandler();

private:
	GLFWwindow* glfwwindow;

	struct WindowData
	{
		std::string title;
		unsigned int width, height;
		bool VSync;

		std::function<void(Event&)> eventcallback;

		WindowData() = default;
	} data;