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

	// Prevent having an artifice from low resolution cube map
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Set up the vertices per patch for a tessellation shader
	glPatchParameteri(GL_PATCH_VERTICES, 3);
}

void Graphic::PreCompute()
{
	// Create uniform date for 6 cube map directions
	{
		Mat4f pv_mats[6];
		Mat4f view[6];
		Mat4f projection = Mat4f::Perspective(90, 1, NEARCLIP, FARCLIP);

		view[0] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(1, 0, 0), Vec3f(0, -1, 0));
		view[1] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(-1, 0, 0), Vec3f(0, -1, 0));
		view[2] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, 1, 0), Vec3f(0, 0, 1));
		view[3] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, -1, 0), Vec3f(0, 0, -1));
		view[4] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, 0, 1), Vec3f(0, -1, 0));
		view[5] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, 0, -1), Vec3f(0, -1, 0));

		for (int i = 0; i < 6; i++)
		{
			pv_mats[i] = projection * view[i];
		}

		ConstantData::CubeMap cubemap;
		for (int i = 0; i < 6; i++)
		{
			cubemap.view_perspective_matrix[i] = pv_mats[i];
		}
		auto& data_cubemap = cubemap;
		constant_cubemap.Update(&data_cubemap);
	}

	if (SceneEntity::SkyBoxProxy)
	{
		{
			// Render HDR
			frame_cubemap.BindFrame();
			SceneEntity::SkyBoxProxy->states[0]->BindTextureUnit();
			frame_cubemap.RenderOnce();
		}

		// Create irradiance map
		{
			frame_irradiance.BindFrame();
			frame_cubemap.BindTextureUnit();
			frame_irradiance.RenderOnce();
		}

		// Create specular map
		{
			frame_specular.BindFrame();
			frame_cubemap.BindTextureUnit();
			frame_specular.RenderOnce();
		}

		// Create BRDF look up texture
		{
			frame_brdf.BindFrame();
			frame_brdf.RenderOnce();
		}
	}
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

	// Render shadow to frame buffers
	for (int i = 0; i < MAX_POINT_LIGHT_NUM; i++)
	{
		// Submit shadow uniform data
		auto& data_shadow = i_data->shadow[i];
		constant_cubemap.Update(&data_shadow);

		frame_shadowcubemaps[i].BindFrame();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			for (int j = 0; j < SceneEntity::List.size(); j++)
			{
				if (i_data->model_data.size() != 0)
				{
					auto& data_model = i_data->model_data[j];
					constant_model.Update(&data_model);

					SceneEntity::List[j]->DrawMesh();
				}
			}
		}
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

				// Bind shadow map texture 
				for (int j = 0; j < MAX_POINT_LIGHT_NUM; j++)
				{
					frame_shadowcubemaps[j].BindTextureUnit();
				}
				// Bind irradiance map texture
				frame_irradiance.BindTextureUnit();
				// Bind specular map texture
				frame_specular.BindTextureUnit();
				// Bind brdf look up texture
				frame_brdf.BindTextureUnit();
				SceneEntity::List[i]->Draw();
			}
		}

		//Rendering sky box
		if (SceneEntity::SkyBoxProxy)
		{
			glDepthFunc(GL_LEQUAL);
			ConstantData::SkyBox data_skybox;
			data_skybox.skybox_view_perspective_matrix = i_data->camera.perspective_matrix * Mat4f::TruncateToMat3(i_data->camera.view_matrix);
			constant_skybox.Update(&data_skybox);

			frame_cubemap.BindTextureUnit();
			SceneEntity::SkyBoxProxy->Draw();
			glDepthFunc(GL_LESS);
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
