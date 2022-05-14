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
		Mat4f projection = Mat4f::Perspective(90, 1, NearClip, FarClip);

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
		ConstBufferCubeMap.Update(&data_cubemap);
	}

	if (SceneEntity::SkyBoxProxy)
	{
		glCullFace(GL_FRONT);

		// Render HDR
		{
			FrameBufferCubeMap.BindFrame();
			SceneEntity::SkyBoxProxy->state->BindTextureUnit();
			FrameBufferCubeMap.RenderOnce();
		}		

		// Create irradiance map
		{
			FrameBufferIrradiance.BindFrame();
			FrameBufferCubeMap.BindTextureUnit();
			FrameBufferIrradiance.RenderOnce();
		}

		// Create specular map
		{
			FrameBufferSpecular.BindFrame();
			FrameBufferCubeMap.BindTextureUnit();
			FrameBufferSpecular.RenderOnce();
		}

		glCullFace(GL_BACK);

		// Create BRDF look up texture
		{
			FrameBufferBrdf.BindFrame();
			FrameBufferBrdf.RenderOnce();
		}				
	}
}

void Graphic::PreUpdate(GraphicRequiredData* i_data)
{	
}

void Graphic::Update(GraphicRequiredData* i_data)
{
#ifdef ENGINE_USE_EDITOR

	ConstDataCamera = i_data->editor_camera;
	ConstBufferCamera.Update(&ConstDataCamera);

#else

	// Submit Camera Information
	ConstDataCamera = i_data->camera;
	ConstBufferCamera.Update(&ConstDataCamera);

#endif

	// Submit light uniform data
	auto& data_light = i_data->light;
	ConstBufferLight.Update(&data_light);


	// Render shadow to frame buffers
	for (int i = 0; i < NUM_MAX_POINT_LIGHT; i++)
	{
		// Submit shadow uniform data
		auto& data_shadow = i_data->shadow[i];
		ConstBufferCubeMap.Update(&data_shadow);

		FrameBufferShadowMaps[i].BindFrame();
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			for (int j = 0; j < SceneEntity::List.Size(); j++)
			{
				if (i_data->model_data.Size() != 0)
				{
					auto& data_model = i_data->model_data[j];
					ConstBufferModel.Update(&data_model);

					SceneEntity::List[j]->DrawMeshOnly();
				}
			}
		}
	}

#ifdef ENGINE_USE_EDITOR	

	FrameBufferImage.BindFrame();

#else	

	glViewport(0, 0, ViewportWidth, ViewportHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

#endif // ENGINE_USE_EDITOR	

	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rendering objects
		for (int i = 0; i < SceneEntity::List.Size(); i++)
		{
			if (i_data->model_data.Size() != 0)
			{
				auto& data_model = i_data->model_data[i];
				data_model.model_view_perspective_matrix = ConstDataCamera.perspective_matrix * ConstDataCamera.view_matrix * data_model.model_position_matrix;
				ConstBufferModel.Update(&data_model);

				auto& data_material = i_data->material_data[i];
				ConstBufferMaterial.Update(&data_material);

				auto& data_animation = i_data->animation_bone_data;
				ConstBufferAnimationBone.Update(&data_animation);

				// Bind shadow map texture 
				for (int j = 0; j < NUM_MAX_POINT_LIGHT; j++)
				{
					FrameBufferShadowMaps[j].BindTextureUnit();
				}
				// Bind irradiance map texture
				FrameBufferIrradiance.BindTextureUnit();
				// Bind specular map texture
				FrameBufferSpecular.BindTextureUnit();
				// Bind BRDF look up texture
				FrameBufferBrdf.BindTextureUnit();
				SceneEntity::List[i]->Draw();

				DrawPrimitive::DebugDraw();
			}
		}

		//Rendering sky box
		if (SceneEntity::SkyBoxProxy)
		{
			glDepthFunc(GL_LEQUAL);
			ConstantData::SkyBox data_skybox;
			data_skybox.skybox_view_perspective_matrix = ConstDataCamera.perspective_matrix * Mat4f::TruncateToMat3(ConstDataCamera.view_matrix);
			ConstBufferSkybox.Update(&data_skybox);

			FrameBufferCubeMap.BindTextureUnit();
			SceneEntity::SkyBoxProxy->Draw();
			glDepthFunc(GL_LESS);
		}
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
