#pragma once

public:

	void SetVSync(bool i_enable);
	bool isVSync() {return data.VSync;}

	void Init(const WindowProperty& property);
	bool CheckShutdown();
	void SwapBuffer();
	void Shutdown();


	HWND GetNaitiveWindowsHandler();
	GLFWwindow* GetGLFWWindow();
	Array<const char*> GetRequiredExtensions();

private:
	GLFWwindow* glfwwindow;
	Array<const char*> extensions;