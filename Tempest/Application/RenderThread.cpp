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

	void RenderThread::CriticalSection()
	{		
		std::swap(ContainerGameOwn, ContainerRenderOwn);
	}

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