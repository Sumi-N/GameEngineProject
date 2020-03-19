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

	// Submit model matrix
	{
		for (auto it = SceneFormat::List.begin(); it != SceneFormat::List.end(); ++it)
		{
			ConstantData::Model model;
			model.model_inverse_transpose_matrix = (*it).proxy->mesh->model_inverse_transpose_mat;
			model.model_position_matrix          = (*it).proxy->mesh->model_mat;

			data_game_own->model_data.push_back(model);
		}
	}

}