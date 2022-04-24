#include "RenderThread.h"

namespace Tempest
{

	//Data required for render thread
	GraphicRequiredData  ContainerRenderData[2];
	GraphicRequiredData* ContainerGameOwn = &ContainerRenderData[0];
	GraphicRequiredData* ContainerRenderOwn = &ContainerRenderData[1];

	extern HWND WindowsHanlder;

	void RenderThread::Boot()
	{
		// Create window and init glfw
		window = new Window();
		WindowProperty property;
		window->Init(property);

		WindowsHanlder = window->GetNaitiveWindowsHandler();

		// Bind event callbacks including the callbacks that are in imgui layer and other layers 
		BindEvent();

		// Initialize OpenGL
		Graphic::Boot();

		LayerStack::Boot();
	}

	void RenderThread::Init()
	{
		// Init scene Entity
		SceneEntity::Init();

		Graphic::Init(window->data.width, window->data.height);
		
		Graphic::PreCompute();

		EntityCopy::Init();
	}

	void RenderThread::CriticalSection()
	{
		std::swap(ContainerGameOwn, ContainerRenderOwn);
		bready = true;
	}

	void RenderThread::NonCriticalSection()
	{
		if (!window->CheckShutdown())
		{
			brunning = false;
		}

		ParseGraphicsData(ContainerRenderOwn);

		Graphic::PreUpdate(ContainerRenderOwn);

		Graphic::Update(ContainerRenderOwn);

		LayerStack::Update();

		Graphic::PostUpdate(ContainerRenderOwn);				

		window->SwapBuffer();
	}

	void RenderThread::SecondCriticalSection()
	{
		LayerStack::Update2();
	}

	void RenderThread::FollowupSection()
	{
		bready = false;
	}

	//inline void RenderThread::Run()
	//{
	//	bool brunning = true;
	//
	//	while (brunning)
	//	{
	//
	//		// Reading this comment section along with GameThread.h is recommended
	//		// The purpose for this section is to swap data between game thread and render thread while the game thread is waiting
	//		{
	//			// 1. The purpose for lock_guard_render is to not let the game thread to touch both the swapping data and b_render_ready variable
	//			// Especially the game thread is constantly referencing b_render_ready variable so it is important to lock the variable when this thread make a change to it
	//			std::lock_guard<std::mutex> lock_guard_render(Mutex_Render);
	//
	//			{
	//				std::swap(data_game_own, data_render_own);
	//			}
	//
	//			// 3. Make b_render_ready true so that it goes through while loop in the game thread 
	//			b_render_ready = true;
	//			// 4. Notify unique_lock_guard_render mutex to release the lock
	//			Condition_Render.notify_one();
	//		}
	//
	//		{
	//			if (!Graphic::PreUpdate())
	//			{
	//				brunning = false;
	//			}
	//
	//			Graphic::Update(data_render_own);
	//
	//			Graphic::PostUpdate(data_render_own);
	//		}
	//
	//		// Almost the same logic as the section below. see the comments below.
	//		{
	//			std::unique_lock<std::mutex> unique_lock_guard_game(Mutex_Game);
	//
	//			while (!b_game_ready)
	//			{
	//				Condition_Game.wait(unique_lock_guard_game);
	//			}
	//		}
	//
	//		b_render_ready = false;
	//	}
	//
	//	CleanUp();
	//}

	void RenderThread::CleanUp()
	{
		LayerStack::CleanUp();
		Graphic::CleanUp();
		window->Shutdown();
		delete window;
	}

	void RenderThread::ParseGraphicsData(GraphicRequiredData* i_data) 
	{		
		// Submit point data 
		//{
		//	Debug::Ray ray;
		//	ray.startpoint = EntityCopy::CamerasObjectsCopy[0]->pos;
		//	ray.direction = 2 * (UserInput.X() / ScreenWidth - 0.5f) * EntityCopy::CamerasObjectsCopy[0]->GetRightVec()
		//		- 2 * (UserInput.Y() / ScreenHeight - 0.5f) * EntityCopy::CamerasObjectsCopy[0]->GetUpVec()
		//		+ EntityCopy::CamerasObjectsCopy[0]->GetForwardVec();
		//	ray.GetEndPoint();
		//	i_data->points[0] = ray.startpoint + 0.1f * EntityCopy::CamerasObjectsCopy[0]->GetForwardVec();
		//	i_data->points[1] = ray.endpoint;
		//}

		// Submit camera data
		{
			i_data->camera.camera_position_vector = EntityCopy::CamerasObjectsCopy[0]->pos;
			i_data->camera.perspective_matrix = EntityCopy::CamerasObjectsCopy[0]->perspective;
			i_data->camera.view_matrix = EntityCopy::CamerasObjectsCopy[0]->view;
		}

		// Submit lights data
		{
			// Submit ambient light data
			i_data->light.ambient_intensity = Vec4f(EntityCopy::AmbientLightCopy->intensity);

			// Submit directional light data
			i_data->light.directional_intensity = Vec4f(EntityCopy::DirectionalLightCopy->intensity);
			i_data->light.directional_direction = Vec4f(EntityCopy::DirectionalLightCopy->direction);
			//data_game_own->shadow.directional_view_perspective_matrix = EntityCopy::Directional->light_space_mat;

			// Submit point lights data
			if (EntityCopy::PointLightListCopy.Size() != 0)
			{
				i_data->light.point_num = static_cast<int>(EntityCopy::PointLightListCopy.Size());

				for (auto it = EntityCopy::PointLightListCopy.Begin(); it != EntityCopy::PointLightListCopy.End(); ++it)
				{
					// Submit point light data					
					i_data->light.pointlights[Utility::Distance<OwningPointer<PointLight>>(EntityCopy::PointLightListCopy.Begin(), it)].intensity = Vec4f((*it)->intensity);
					i_data->light.pointlights[Utility::Distance<OwningPointer<PointLight>>(EntityCopy::PointLightListCopy.Begin(), it)].position = Vec4f((*it)->pos);
					i_data->light.pointlights[Utility::Distance<OwningPointer<PointLight>>(EntityCopy::PointLightListCopy.Begin(), it)].attenuation = (*it)->attenuation;

					for (int i = 0; i < 6; i++)
					{
						i_data->shadow[Utility::Distance<OwningPointer<PointLight>>(EntityCopy::PointLightListCopy.Begin(), it)].view_perspective_matrix[i] = (*it)->light_space_mats[i];
						i_data->shadow[Utility::Distance<OwningPointer<PointLight>>(EntityCopy::PointLightListCopy.Begin(), it)].position = Vec4f((*it)->pos);
					}
				}
			}
		}

		{
			//for (auto it = SceneEntityCopy::List.Begin(); it != SceneEntityCopy::List.End(); ++it)
			for (auto it = EntityCopy::MeshComponentListCopy.Begin(); it != EntityCopy::MeshComponentListCopy.End(); ++it)
			{
				// Submit mesh data
				ConstantData::Model model;
				model.model_inverse_transpose_matrix = (*it)->model_inverse_transpose_mat;
				model.model_position_matrix = (*it)->model_mat;
				i_data->model_data.PushBack(model);
			}

			for (auto it = EntityCopy::EffectComponentListCopy.Begin(); it != EntityCopy::EffectComponentListCopy.End(); ++it)
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

		//{
		//	for (int i = 0; i < NUM_MAX_BONES; i++)
		//	{
		//		i_data->animation_bone_data.global_inversed_matrix[i] = EntityCopy::Animation.bones[i];
		//	}
		//}
	}

	void RenderThread::BindEvent()
	{
		window->data.eventcallback = std::bind(&RenderThread::OnEvent, this, std::placeholders::_1);
	}

	void RenderThread::OnEvent(Event& i_event)
	{
		EventDispatcher dispatcher(i_event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&RenderThread::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&RenderThread::OnWindowResize, this, std::placeholders::_1));

		LayerStack::OnEvent(i_event);
	}

	bool RenderThread::OnWindowClose(WindowCloseEvent i_event)
	{
		window->OnWindowClose(i_event);
		return true;
	}

	bool RenderThread::OnWindowResize(WindowResizeEvent i_event)
	{
		Graphic::ChangeViewPortSize(window->data.width, window->data.height);
		window->OnWindowResize(i_event);
		return true;
	}

}