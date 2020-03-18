#pragma once
#include "Input.OpenGL.h"

void GLFW_INPUT::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	for (int i = 32; i < 90; i++)
	{
		if (key == i && (action == GLFW_PRESS || action == GLFW_REPEAT))
		{
			input_render_own->RegisterKey(i, true);
		}
		else
		{
			input_render_own->RegisterKey(i, false);
		}
	}
}

void GLFW_INPUT::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			//mousestate.isRightButtonPressing = true;
		}
		else
		{
			//mousestate.isRightButtonPressing = false;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			//mousestate.isLeftButtonPressing = true;
		}
		else if (action == GLFW_RELEASE)
		{
			//mousestate.isLeftButtonPressing = false;
		}
	}
}

void GLFW_INPUT::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	//mousestate.oldxpos = mousestate.xpos;
	//mousestate.oldypos = mousestate.ypos;
	//mousestate.xpos = xpos;
	//mousestate.ypos = ypos;

	//if (mousestate.isRightButtonPressing)
	//{
	//	float rotationratex = (float)(mousestate.xpos - mousestate.oldxpos);
	//	float rotationratey = (float)(mousestate.ypos - mousestate.oldypos);

	//	BeginSubmittedByRenderThread->rotationratex = rotationratex;
	//	BeginSubmittedByRenderThread->rotationratey = rotationratey;
	//}

	return;
}