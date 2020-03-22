#pragma once

#include "Define.h"
#include "Thread.h"
#include "RenderThread.h"

class GameThread : public Thread
{
public:
	void Boot() override;
	void Init() override;
	void Run() override;
	void CleanUp() override;
	void Eject() override;

	void PassDataTo(Thread *) override;
};

inline void GameThread::Boot()
{
}

inline void GameThread::Init()
{
	Time::Init();
	Entity::Init();
	UserInput.Init();
}

inline void GameThread::Run()
{
	while (true)
	{
		UserInput.Populate(*input_update_list_game_own);

		Time::Update();
		Entity::Update(static_cast<float>(Time::dt));

		{
			std::unique_lock<std::mutex> unique_lock_guard(Mutex_Render);
			while (!b_render_ready)
				Condition_Render.wait(unique_lock_guard);
			{
				PassDataTo(&Thread_Render);
			}
			b_render_ready = false;
		}
	}
}

inline void GameThread::CleanUp()
{

}

inline void GameThread::Eject()
{

}

inline void GameThread::PassDataTo(Thread * io_thread)
{
	RenderThread * render_thread = static_cast<RenderThread*>(io_thread);

	if(render_thread)
	{
		
	}

	
	// Submit camera data
	{
		data_game_own->camera.camera_position_vector = Entity::CurrentCamera->pos;
		data_game_own->camera.perspective_matrix     = Entity::CurrentCamera->perspective;
		data_game_own->camera.view_matrix            = Entity::CurrentCamera->view;
	}

	// Submit lights data
	{
		// Submit ambient light data
		data_game_own->light.ambient_intensity = Vec4f(Entity::Ambient->intensity);

		// Submit directional light data
		//data_game_own->light.directional_intensity = Vec4f(Entity::Directional->intensity);
		//data_game_own->light.directional_direction = Vec4f(Entity::Directional->direction);

		// Submit point light data
		if (Entity::PointLightList.size() != 0)
		{
			data_game_own->light.point_num = static_cast<int>(Entity::PointLightList.size());

			for (auto it = Entity::PointLightList.begin(); it != Entity::PointLightList.end(); ++it)
			{
				data_game_own->light.pointlights[std::distance(Entity::PointLightList.begin(), it)].point_intensity = Vec4f((*it)->intensity);
				data_game_own->light.pointlights[std::distance(Entity::PointLightList.begin(), it)].point_position = Vec4f((*it)->pos);
			}
		}
	}

	// Submit object data
	{
		for (auto it = SceneFormat::List.begin(); it != SceneFormat::List.end(); ++it)
		{
			// Submit material data
			ConstantData::Material material;
			material.diffuse                     = Vec4f((*it).proxy->mesh->material->Kd, 1.0f);
			material.specular                    = Vec4f((*it).proxy->mesh->material->Ks, (*it).proxy->mesh->material->Ns);
			data_game_own->material_data.push_back(material);

			// Submit mesh data
			ConstantData::Model model;
			model.model_inverse_transpose_matrix = (*it).proxy->mesh->model_inverse_transpose_mat;
			model.model_position_matrix          = (*it).proxy->mesh->model_mat;

			data_game_own->model_data.push_back(model);
		}
	}

}