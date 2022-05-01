#include "GameThread.h"


namespace Tempest
{	
	extern GraphicRequiredData GraphicsData;
	HWND WindowsHanlder;
	Time GameThreadTime;

	void WriteDataToOwningThread(GraphicRequiredData*);

	void GameThread::Boot()
	{
		Entity::Boot();
	}

	void GameThread::Init()
	{
		Time::Init();
		UserInput.Init();
		Entity::Init();				

#ifdef ENGINE_PLATFORM_WINDOWS
		UserInput.GetWindowsHandler(WindowsHanlder);
#endif // ENGINE_PLATFORM_WINDOWS

	}

	void GameThread::NonCriticalSection()
	{
		UserInput.Populate();
		Time::Update(GameThreadTime);
		Entity::Update(static_cast<float>(GameThreadTime.dt));
	}

	void GameThread::CriticalSection()
	{
		WriteDataToOwningThread(&GraphicsData);
	}

	void GameThread::CleanUp()
	{
	}

	void WriteDataToOwningThread(GraphicRequiredData* i_data)
	{
		//Submit point data 
		{
			Debug::Ray ray;
			ray.startpoint = Entity::CamerasObjects[0]->pos;
			ray.direction = 2 * (UserInput.X() / ScreenWidth - 0.5f) * Entity::CamerasObjects[0]->GetRightVec()
				- 2 * (UserInput.Y() / ScreenHeight - 0.5f) * Entity::CamerasObjects[0]->GetUpVec()
				+ Entity::CamerasObjects[0]->GetForwardVec();
			ray.GetEndPoint();
			//i_data->points[0] = ray.startpoint + 0.1f * Entity::CamerasObjects[0]->GetForwardVec();
			//i_data->points[1] = ray.endpoint;
		}

		// Submit camera data
		{
			i_data->camera.camera_position_vector = Entity::CamerasObjects[0]->pos;
			i_data->camera.perspective_matrix = Entity::CamerasObjects[0]->perspective;
			i_data->camera.view_matrix = Entity::CamerasObjects[0]->view;
		}

		// Submit lights data
		{
			// Submit ambient light data
			i_data->light.ambient_intensity = Vec4f(Entity::Ambient->intensity);

			// Submit directional light data
			i_data->light.directional_intensity = Vec4f(Entity::Directional->intensity);
			i_data->light.directional_direction = Vec4f(Entity::Directional->direction);
			//data_game_own->shadow.directional_view_perspective_matrix = EntityCopy::Directional->light_space_mat;

			// Submit point lights data
			if (Entity::PointLightList.Size() != 0)
			{
				i_data->light.point_num = static_cast<int>(Entity::PointLightList.Size());

				for (auto it = Entity::PointLightList.Begin(); it != Entity::PointLightList.End(); ++it)
				{
					// Submit point light data					
					i_data->light.pointlights[Utility::Distance<OwningPointer<PointLight>>(Entity::PointLightList.Begin(), it)].intensity = Vec4f((*it)->intensity);
					i_data->light.pointlights[Utility::Distance<OwningPointer<PointLight>>(Entity::PointLightList.Begin(), it)].position = Vec4f((*it)->pos);
					i_data->light.pointlights[Utility::Distance<OwningPointer<PointLight>>(Entity::PointLightList.Begin(), it)].attenuation = (*it)->attenuation;

					for (int i = 0; i < 6; i++)
					{
						i_data->shadow[Utility::Distance<OwningPointer<PointLight>>(Entity::PointLightList.Begin(), it)].view_perspective_matrix[i] = (*it)->light_space_mats[i];
						i_data->shadow[Utility::Distance<OwningPointer<PointLight>>(Entity::PointLightList.Begin(), it)].position = Vec4f((*it)->pos);
					}
				}
			}
		}

		{
			//for (auto it = SceneEntityCopy::List.Begin(); it != SceneEntityCopy::List.End(); ++it)
			for (auto it = Entity::MeshComponentList.Begin(); it != Entity::MeshComponentList.End(); ++it)
			{
				// Submit mesh data
				ConstantData::Model model;
				model.model_inverse_transpose_matrix = (*it)->model_inverse_transpose_mat;
				model.model_position_matrix = (*it)->model_mat;
				i_data->model_data.PushBack(model);
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
				i_data->material_data.PushBack(material);
			}
		}

		{
			for (int i = 0; i < NUM_MAX_BONES; i++)
			{
				i_data->animation_bone_data.global_inversed_matrix[i] = Entity::Animation.bones[i];
			}
		}
	}
}