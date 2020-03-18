#pragma once

#include "Define.h"

#ifdef ENGINE_GRAPHIC_OPENGL

namespace GLFW_INPUT
{
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
}

#endif // ENGINE_GRAPHIC_OPENGL
