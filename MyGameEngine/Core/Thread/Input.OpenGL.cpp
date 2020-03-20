#pragma once
#include "Input.OpenGL.h"

void GLFW_INPUT::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	std::pair<unsigned int, bool> pair;

	for (int i = 0; i < 256; i++)
	{
		if (key == i && action == GLFW_PRESS)
		{
			pair = {i, true};
			input_update_list_render_own->keys.push_back(pair);
		}
		else if(key == i && action == GLFW_RELEASE)
		{
			pair = {i, false};
			input_update_list_render_own->keys.push_back(pair);
		}
	}
}

void GLFW_INPUT::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

	std::pair<unsigned int, bool> pair;

	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			pair = { 0x02, true };
			input_update_list_render_own->keys.push_back(pair);
		}
		else if(action == GLFW_RELEASE)
		{
			pair = { 0x02, false };
			input_update_list_render_own->keys.push_back(pair);
		}
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			pair = { 0x01, true };
			input_update_list_render_own->keys.push_back(pair);
		}
		else if (action == GLFW_RELEASE)
		{
			pair = { 0x01, false };
			input_update_list_render_own->keys.push_back(pair);
		}
	}
}

void GLFW_INPUT::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	input_update_list_render_own->x = xpos;
	input_update_list_render_own->y = ypos;

	return;
}