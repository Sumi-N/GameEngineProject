#pragma  once
// This should be included first
#include "ImguiLayer.h"

#include <Application/Application.h>
#include <Application/EntryPoint.h>
#include "../MyGame/MyCameraObject.h"

namespace Tempest
{

	class Editor : public Application
	{
	public:
		Editor();
		~Editor() = default;
	};

	Editor::Editor()
	{
		Application::Execute();
	}


	Tempest::Application* Tempest::Create()
	{
		Owner<Object> camera = Create<MyCameraObject>();
		Entity::Register(camera);

		Owner<Object> model = Create<Object>();
		model->Translate(Vec3f(0, -20, -70));
		model->scale = 0.35f;
		Owner<MeshComponent> mesh_component = Create<MeshComponent>();
		mesh_component->owner = model;
		Entity::RegisterMeshComponent(mesh_component);
		Entity::Register(model);

		ImguiLayer* imgui_layer = new ImguiLayer();
		LayerStack::PushLayer(imgui_layer);
		return new Editor();
	}

}