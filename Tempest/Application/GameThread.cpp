#include "GameThread.h"


namespace Tempest
{
	extern GraphicRequiredData* data_game_own;
	extern GraphicRequiredData* data_render_own;

	HWND WindowsHanlder;

	void GameThread::Boot()
	{
		Entity::Boot();
	}

	void GameThread::Init()
	{
		Time::Init();
		Entity::Init();
		UserInput.Init();

#ifdef ENGINE_PLATFORM_WINDOWS
		UserInput.InitForWindows(WindowsHanlder);
#endif // ENGINE_PLATFORM_WINDOWS

	}

	void GameThread::CriticalSection()
	{
		bready = false;
		UserInput.Populate();
		Time::Update();
		Entity::Update(static_cast<float>(Time::dt));
		bready = true;
	}

	void GameThread::NonCriticalSection()
	{
	}

	void GameThread::SecondCriticalSection()
	{
		WriteDataToOwningThread();
	}

	void GameThread::FollowupSection()
	{
		*ThreadManager::b_thread_ready[ThreadManager::GetOtherThreadID(thread_id)] = false;
	}

	//inline void GameThread::Run()
	//{
	//	while (true)
	//	{
	//		// Almost the same logic as the section below. see the comments below.
	//		{
	//			std::lock_guard<std::mutex> lock_guard_game(Mutex_Game);
	//
	//			b_game_ready = false;
	//
	//			{
	//				UserInput.Populate();
	//				Time::Update();
	//				Entity::Update(static_cast<float>(Time::dt));
	//			}
	//
	//			b_game_ready = true;
	//			Condition_Game.notify_one();
	//		}
	//
	//		// Reading this comment section along with RenderThread.h is recommended
	//		// The purpose for this section is to wait for the render thread to finish swapping data
	//		{
	//			// 2. unique_lock_guard_render will block the thread until b_render_ready become true
	//			// The reason this is unique_lock is because this lock has to be released from the render thread 
	//			std::unique_lock<std::mutex> unique_lock_guard_render(Mutex_Render);
	//
	//			// 5. Block the logic until the render thread finishing swapping
	//			while (!b_render_ready)
	//			{
	//				Condition_Render.wait(unique_lock_guard_render);
	//			}
	//
	//			{
	//				WriteDataToOwningThread();
	//			}
	//
	//			// 6. After finish writing the data, make b_render_ready true 
	//			// So that the render thread wouldn't render the same scene more than one
	//			b_render_ready = false;
	//		}
	//	}
	//}

	void GameThread::CleanUp()
	{

	}

	void GameThread::WriteDataToOwningThread()
	{
		// Submit point data 
		{
			Debug::Ray ray;
			ray.startpoint = Entity::CamerasObjects[0]->pos;
			ray.direction = 2 * (UserInput.X() / SCREEN_WIDTH - 0.5f) * Entity::CamerasObjects[0]->GetRightVec()
				- 2 * (UserInput.Y() / SCREEN_HEIGHT - 0.5f) * Entity::CamerasObjects[0]->GetUpVec()
				+ Entity::CamerasObjects[0]->GetForwardVec();
			ray.GetEndPoint();
			data_game_own->points[0] = ray.startpoint + 0.1f * Entity::CamerasObjects[0]->GetForwardVec();
			data_game_own->points[1] = ray.endpoint;
		}

		// Submit camera data
		{
			data_game_own->camera.camera_position_vector = Entity::CamerasObjects[0]->pos;
			data_game_own->camera.perspective_matrix = Entity::CamerasObjects[0]->perspective;
			data_game_own->camera.view_matrix = Entity::CamerasObjects[0]->view;
		}

		// Submit lights data
		{
			// Submit ambient light data
			data_game_own->light.ambient_intensity = Vec4f(Entity::Ambient->intensity);

			// Submit directional light data
			data_game_own->light.directional_intensity = Vec4f(Entity::Directional->intensity);
			data_game_own->light.directional_direction = Vec4f(Entity::Directional->direction);
			//data_game_own->shadow.directional_view_perspective_matrix = Entity::Directional->light_space_mat;

			// Submit point lights data
			if (Entity::PointLightList.Size() != 0)
			{
				data_game_own->light.point_num = static_cast<int>(Entity::PointLightList.Size());

				for (auto it = Entity::PointLightList.Begin(); it != Entity::PointLightList.End(); ++it)
				{
					// Submit point light data					
					data_game_own->light.pointlights[Utility::Distance<OwningPointer<PointLight>>(Entity::PointLightList.Begin(), it)].intensity = Vec4f((*it)->intensity);
					data_game_own->light.pointlights[Utility::Distance<OwningPointer<PointLight>>(Entity::PointLightList.Begin(), it)].position = Vec4f((*it)->pos);
					data_game_own->light.pointlights[Utility::Distance<OwningPointer<PointLight>>(Entity::PointLightList.Begin(), it)].attenuation = (*it)->attenuation;

					for (int i = 0; i < 6; i++)
					{
						data_game_own->shadow[Utility::Distance<OwningPointer<PointLight>>(Entity::PointLightList.Begin(), it)].view_perspective_matrix[i] = (*it)->light_space_mats[i];
						data_game_own->shadow[Utility::Distance<OwningPointer<PointLight>>(Entity::PointLightList.Begin(), it)].position = Vec4f((*it)->pos);
					}
				}
			}
		}

		{
			//for (auto it = SceneEntity::List.Begin(); it != SceneEntity::List.End(); ++it)
			for (auto it = Entity::MeshComponentList.Begin(); it != Entity::MeshComponentList.End(); ++it)
			{
				// Submit mesh data
				ConstantData::Model model;
				model.model_inverse_transpose_matrix = (*it)->model_inverse_transpose_mat;
				model.model_position_matrix = (*it)->model_mat;
				data_game_own->model_data.PushBack(model);		
			}

			for (auto it = Entity::EffectComponentList.Begin(); it != Entity::EffectComponentList.End(); ++it)
			{
				// Submit material data
				ConstantData::Material material;
				material.diffuse = Vec4f(0.5f, 0.0f, 0.0f, 1.0f);
				material.specular = Vec4f(0.8f, 0.8f, 0.8f, 10.0f);
				material.albedo = (*it)->material_attribute->material->albedo;
				material.metalic = (*it)->material_attribute->material->metalic;
				material.roughness = (*it)->material_attribute->material->roughness;
				data_game_own->material_data.PushBack(material);
			}
		}
	}
}