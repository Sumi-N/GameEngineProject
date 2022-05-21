#pragma  once
// This should be included first
#include "ImguiLayer.h"

#include <Application/Application.h>
#include <Application/EntryPoint.h>

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
		ImguiLayer* imgui_layer = new ImguiLayer();
		LayerStack::PushLayer(imgui_layer);
		return new Editor();
	}

}