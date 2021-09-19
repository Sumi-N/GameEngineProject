#pragma once
#include "Graphic.h"

#ifdef  ENGINE_GRAPHIC_OPENGL

void Graphic::Boot()
{
	// Set background color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	glEnable(GL_DEPTH_TEST);

	// Set up culling
	glEnable(GL_CULL_FACE);

	// Prevent having an artifice from low resolution cube map
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Set up the vertices per patch for a tessellation shader
	glPatchParameteri(GL_PATCH_VERTICES, 3);
}

void Graphic::PreCompute()
{
	// Create uniform date for 6 directions of the cube map
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
		glCullFace(GL_FRONT);

		// Render HDR
		{
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

		glCullFace(GL_BACK);

		// Create BRDF look up texture
		{
			frame_brdf.BindFrame();
			frame_brdf.RenderOnce();
		}				
	}
}

void Graphic::PreUpdate()
{
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
	for (int i = 0; i < NUM_MAX_POINT_LIGHT; i++)
	{
		// Submit shadow uniform data
		auto& data_shadow = i_data->shadow[i];
		constant_cubemap.Update(&data_shadow);

		frame_shadowcubemaps[i].BindFrame();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			for (int j = 0; j < SceneEntity::List.Size(); j++)
			{
				if (i_data->model_data.Size() != 0)
				{
					auto& data_model = i_data->model_data[j];
					constant_model.Update(&data_model);

					SceneEntity::List[j]->DrawMeshOnly();
				}
			}
		}
	}

	glViewport(0, 0, viewport_width, viewport_height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rendering objects
		for (int i = 0; i < SceneEntity::List.Size(); i++)
		{
			if (i_data->model_data.Size() != 0)
			{
				auto& data_model = i_data->model_data[i];
				data_model.model_view_perspective_matrix = data_camera.perspective_matrix * data_camera.view_matrix * data_model.model_position_matrix;
				constant_model.Update(&data_model);

				auto& data_material = i_data->material_data[i];
				constant_material.Update(&data_material);

				auto& data_animation = i_data->animation_bone_data;
				constant_animationbone.Update(&data_animation);

				// Bind shadow map texture 
				for (int j = 0; j < NUM_MAX_POINT_LIGHT; j++)
				{
					frame_shadowcubemaps[j].BindTextureUnit();
				}
				// Bind irradiance map texture
				frame_irradiance.BindTextureUnit();
				// Bind specular map texture
				frame_specular.BindTextureUnit();
				// Bind BRDF look up texture
				frame_brdf.BindTextureUnit();
				SceneEntity::List[i]->Draw();

				DrawPrimitive::DebugDraw();
			}
		}

		//DrawPrimitive::DebugDraw();
		//Draw a line mainly for the purpose for debug
		//DrawPrimitive::DrawLineWithShader(i_data->points[0], i_data->points[1]);

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
	i_data->model_data.Clear();
	i_data->material_data.Clear();	
}

void Graphic::CleanUp()
{
}

#endif // ENGINE_GRAPHIC_OPENGL
