#include "RenderThread.h"

namespace Tempest
{		
	extern HWND WindowsHanlder;	
	GraphicRequiredData  GraphicsData;
	void WriteDataToOwningThread(GraphicRequiredData* i_data);

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
	}

	void RenderThread::Init()
	{		
		// Init scene Entity
		SceneEntity::Init();

		Graphic::Init(window->data.width, window->data.height);

		LayerStack::Init();
		
		Graphic::PreCompute();
	}

	void RenderThread::Reset()
	{
		SceneEntity::Init();
		Graphic::PreCompute();
	}

	void RenderThread::NonCriticalSection()
	{		
		if (!window->CheckShutdown())
		{
			brunning = false;
		}		
		
		Graphic::PreUpdate(&GraphicsData);

		Graphic::Update(&GraphicsData);

		LayerStack::Update();

		Graphic::PostUpdate(&GraphicsData);

		window->SwapBuffer();		
	}

	void RenderThread::CriticalSection()
	{
		WriteDataToOwningThread(&GraphicsData);
		LayerStack::OnCriticalSection();
	}

	void RenderThread::CleanUp()
	{
		LayerStack::CleanUp();		
		Graphic::CleanUp();
		window->Shutdown();
		delete window;
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

	void WriteDataToOwningThread(GraphicRequiredData* i_data)
	{
		// Submit camera data
		{
			i_data->camera.camera_position_vector = Entity::CameraComponentList[0]->owner->pos;
			i_data->camera.perspective_matrix = Entity::CameraComponentList[0]->perspective;
			i_data->camera.view_matrix = Entity::CameraComponentList[0]->view;
		}

		// Submit lights data
		{
			i_data->light.point_num = 0;

			for (auto it = Entity::LightComponentList.Begin(); it != Entity::LightComponentList.End(); ++it)
			{
				switch ((*it)->light_type)
				{
				case LightType::AmbientLight:
				{
					i_data->light.ambient_intensity = Vec4f((*it)->intensity);
				}
				break;
				case LightType::DirectionalLight:
				{
					i_data->light.directional_intensity = Vec4f((*it)->intensity);
					i_data->light.directional_direction = Vec4f((*it)->direction);
				}
				break;
				case LightType::PointLight:
				{
					i_data->light.pointlights[i_data->light.point_num].intensity = Vec4f((*it)->intensity);
					i_data->light.pointlights[i_data->light.point_num].position = Vec4f((*it)->owner->pos);
					i_data->light.pointlights[i_data->light.point_num].attenuation = (*it)->attenuation;

					for (int i = 0; i < 6; i++)
					{
						i_data->shadow[i_data->light.point_num].view_perspective_matrix[i] = (*it)->light_space_mats[i];
						i_data->shadow[i_data->light.point_num].position = Vec4f((*it)->owner->pos);
					}

					i_data->light.point_num++;
				}
				break;
				default:
					DEBUG_ASSERT(false);
					break;
				}
			}
		}

		{
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
				material.albedo = (*it)->material.albedo;
				material.metalic = (*it)->material.metalic;
				material.roughness = (*it)->material.roughness;
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