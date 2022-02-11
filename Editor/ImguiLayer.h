#pragma once

#define IMGUI_IMPL_API
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <Application/Window.h>
#include <Layer/Layer.h>
#include <Graphics/Define.h>
#include <Graphics/Graphic.h>

namespace Tempest
{
	extern Window* window;

	class ImguiLayer : public Layer
	{
	public:
		ImguiLayer() = default;
		~ImguiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();

	private:
		void Docking();		
		void ViewportWindow();
		void AssetPanelWindow();
		void ControlPanelWindow();
		void LevelEditorPanelWindow();

	private:
		GLFWwindow* glfw_window = nullptr;
	};

}