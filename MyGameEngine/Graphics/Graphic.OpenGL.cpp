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
	

	// Init uniform buffers
	buffer_camera.Init(ConstantData::Index::Camera, ConstantData::Size::Camera);
	buffer_light.Init(ConstantData::Index::Light, ConstantData::Size::Light);
	buffer_model.Init(ConstantData::Index::Model, ConstantData::Size::Model);
}

void Graphic::PreUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Graphic::Update(GraphicRequiredData * i_data)
{

	// Update uniform data common for frame
	// Submit Camera Information
	auto& data_camera = i_data->camera;
	buffer_camera.Update(&data_camera);

	// Submit Light Information
	auto& data_light = i_data->light;
	buffer_light.Update(&data_light);
	
	for (auto it = SceneFormat::List.begin(); it != SceneFormat::List.end(); ++it)
	{
		if (i_data->model_data.size() != 0)
		{
			auto& data_model = i_data->model_data[std::distance(SceneFormat::List.begin(), it)];
			data_model.model_view_perspective_matrix = data_camera.perspective_matrix * data_camera.view_matrix * data_model.model_position_matrix;
			//data_model.model_view_perspective_matrix.Transpose();
			buffer_model.Update(&data_model);

			(*it).shader->BindShader();
			(*it).proxy->Draw();
		}
	}
	
}

void Graphic::PostUpdate()
{
	glfwSwapBuffers(window);
}

#endif // ENGINE_GRAPHIC_OPENGL
