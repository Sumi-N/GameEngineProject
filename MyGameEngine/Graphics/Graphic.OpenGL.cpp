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

void renderQuad()
{
	unsigned int quadVAO = 0;
	unsigned int quadVBO;

	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Graphic::PreCompute()
{
	Mat4f light_space_mats[6];
	Mat4f light_view[6];
	Mat4f light_projection = Mat4f::Perspective(90, 1, NEARCLIP, FARCLIP);

	light_view[0] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f( 1, 0, 0), Vec3f(0, -1, 0));
	light_view[1] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(-1, 0, 0), Vec3f(0, -1, 0));
	light_view[2] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0,  1, 0), Vec3f(0, 0, 1));
	light_view[3] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, -1, 0), Vec3f(0, 0, -1));
	light_view[4] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, 0,  1), Vec3f(0, -1, 0));
	light_view[5] = Mat4f::LookAt(Vec3f(0, 0, 0), Vec3f(0, 0, -1), Vec3f(0, -1, 0));

	for (int i = 0; i < 6; i++)
	{
		light_space_mats[i] = light_projection * light_view[i];
	}

	ConstantData::Shadow tmp;
	for (int i = 0; i < 6; i++)
	{
		tmp.point_view_perspective_matrix[i] = light_space_mats[i];
	}
	auto& data_shadow = tmp;
	constant_shadow.Update(&data_shadow);

	// Render HDR
	frame_cubemap.BindFrame();
	glActiveTexture(GL_TEXTURE0 + SceneEntity::SkyBoxScene.skyboxproxy->GetCubeMapTextureUnit());
	glBindTexture(GL_TEXTURE_2D, SceneEntity::SkyBoxScene.skyboxproxy->GetCubeMapTextureID());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SceneEntity::SkyBoxScene.skyboxproxy->Draw();


	///////////////////////////// make irradiance map

	frame_irradiance.BindFrame();
	frame_cubemap.BindTextureUnit();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SceneEntity::SkyBoxScene.skyboxproxy->Draw();

	////////////////////////////  make specular irradiance map
	frame_specular.BindFrame();

	unsigned int maxMipLevels = 5;
	for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
	{
		unsigned int mipWidth = 128 * std::pow(0.5, mip);
		unsigned int mipHeight = 128 * std::pow(0.5, mip);

		glViewport(0, 0, mipWidth, mipHeight);
		float roughness = (float)mip / (float)(maxMipLevels - 1);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, frame_specular.textureid_color, mip);

		GLuint roughness_value = glGetUniformLocation(frame_specular.shader.programid, "roughness");
		glUniform1f(roughness_value, roughness);

		frame_cubemap.BindTextureUnit();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SceneEntity::SkyBoxScene.skyboxproxy->Draw();
	}

	////////////////////////////// BRDF look up texture
	frame_brdf.BindFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderQuad();
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
		constant_shadow.Update(&data_shadow);

		frame_shadow[i].BindFrame();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			for (int j = 0; j < SceneEntity::List.size(); j++)
			{
				if (i_data->model_data.size() != 0)
				{
					auto& data_model = i_data->model_data[j];
					constant_model.Update(&data_model);

					SceneEntity::List[j].proxy->Draw();
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

				// Shadow map texture binding
				for (int j = 0; j < MAX_POINT_LIGHT_NUM; j++)
				{
					frame_shadow[j].BindTextureUnit();
				}
				frame_irradiance.BindTextureUnit();
				frame_specular.BindTextureUnit();
				frame_brdf.BindTextureUnit();
				SceneEntity::List[i].BindAndDraw();
			}
		}

		//Rendering sky box
		if (SceneEntity::SkyBoxScene.skyboxproxy)
		{
			glDepthFunc(GL_LEQUAL);
			ConstantData::SkyBox data_skybox;
			data_skybox.skybox_view_perspective_matrix = i_data->camera.perspective_matrix * Mat4f::TruncateToMat3(i_data->camera.view_matrix);
			constant_skybox.Update(&data_skybox);

			// Doesn't matter whether this is binded or not
			//frame_cubemap.BindTextureUnit();
			SceneEntity::SkyBoxScene.shader->BindShader();
			SceneEntity::SkyBoxScene.skyboxproxy->Draw();
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
