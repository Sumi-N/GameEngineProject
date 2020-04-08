#pragma once
#include "Graphic.h"

#ifdef  ENGINE_GRAPHIC_OPENGL

GLFWwindow * Graphic::window;

void Graphic::Boot()
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

	// Set up culling
	glEnable(GL_DEPTH_TEST);

	// Set up the vertices per patch for a tessellation shader
	glPatchParameteri(GL_PATCH_VERTICES, 3);
}

void Graphic::PreCompute()
{

}

bool Graphic::PreUpdate()
{
	if (glfwWindowShouldClose(window) == GL_TRUE)
		return false;

	glfwPollEvents();

	return true;
}

void Graphic::Update(GraphicRequiredData * i_data)
{

	// Update uniform data common for frame
	// Submit Camera Information
	auto& data_camera = i_data->camera;
	constant_camera.Update(&data_camera);

	// Submit light uniform data
	auto& data_light = i_data->light;
	constant_light.Update(&data_light);

	// Submit shadow uniform data
	auto& data_shadow = i_data->shadow;
	constant_shadow.Update(&data_shadow);

	// Render shadow to frame buffer
	frame_shadow.BindFrame();
	{
		glClear(GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < SceneEntity::List.size(); i++)
		{
			if (i_data->model_data.size() != 0)
			{
				auto& data_model = i_data->model_data[i];
				constant_model.Update(&data_model);

				SceneEntity::List[i].proxy->Draw();
			}
		}
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rendering sky box
		if(SceneEntity::SkyBoxScene.skyboxproxy)
		{
			glDepthMask(GL_FALSE);
			ConstantData::SkyBox data_skybox;
			data_skybox.skybox_view_perspective_matrix = i_data->camera.perspective_matrix * Mat4f::TruncateToMat3(i_data->camera.view_matrix);
			constant_skybox.Update(&data_skybox);

			SceneEntity::SkyBoxScene.shader->BindShader();
			SceneEntity::SkyBoxScene.skyboxproxy->Draw();

			glDepthMask(GL_TRUE);
		}

		// Rendering objects
		for (int i = 0; i < SceneEntity::List.size(); i++)
		{
			if (i_data->model_data.size() != 0)
			{
				auto& data_model = i_data->model_data[i];
				data_model.model_view_perspective_matrix = data_camera.perspective_matrix * data_camera.view_matrix * data_model.model_position_matrix;
				constant_model.Update(&data_model);

				auto& data_material = i_data->material_data[i];
				constant_material.Update(&data_material);

				frame_shadow.BindTextureUnit();
				SceneEntity::List[i].BindAndDraw();
			}
		}
	}
}

void Graphic::PostUpdate(GraphicRequiredData* i_data)
{
	glfwSwapBuffers(window);

	i_data->model_data.clear();
	i_data->material_data.clear();
}

#endif // ENGINE_GRAPHIC_OPENGL
