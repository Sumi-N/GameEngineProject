#pragma once
#include "Graphic.h"

#ifdef  ENGINE_GRAPHIC_OPENGL

GLFWwindow * Graphic::window;

void Graphic::Init()
{
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
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tempest", NULL, NULL);

	if (!window)
	{
		// If the window is not created
		DEBUG_PRINT("Cannot create GLFW window");
		glfwTerminate();
		return;
	}
	// Attached the OpenGL to this window
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		DEBUG_PRINT("Cannot initialize GLFW");
		return;
	}

	// The timing to wait for V-Sync
	glfwSwapInterval(1);

	// Set background color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Set up callback
	//glfwSetKeyCallback(window, Input::keyCallback);
	//glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
	//glfwSetCursorPosCallback(window, Input::cursorPositionCallback);

	// Set up culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
}

void Graphic::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	SceneFormat::Draw();

	glfwSwapBuffers(window);
}

#endif //  
