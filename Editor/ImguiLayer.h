#pragma once

#define IMGUI_IMPL_API
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <Application/Window.h>
#include <Layer/Layer.h>
#include <Graphics/Define.h>
#include <Graphics/Graphic.h>

#include "EntityInfo.h"

namespace Tempest
{
	extern Window* window;
	extern Delegate<> GameThreadOnReset;
	extern Delegate<> RenderThreadOnReset;

	extern bool isEntityModifies;
	extern bool Modified;
	extern int SelectedIndex;
	extern EntityInfo::ComponentFlags SelectedFlag;
	extern EntityInfo::ComponentFlags SelectedObjectFlags;
	extern Object SelectedObject;
	extern CameraComponent SelectedCamera;
	extern LightComponent SelectedLight;
	extern MeshComponent SelectedMesh;
	extern EffectComponent SelecctedEffect;

	class ImguiLayer : public Layer
	{
	public:
		ImguiLayer() = default;
		~ImguiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
		virtual void OnCriticalSection() override;

		void Begin();
		void End();

	private:
		void OnAttach_ViewportPanel();
		void OnAttach_AssetPanel();
		void OnAttach_ControlPanel();
		void OnAttach_SceneEditorPanel();

		void Docking();
		void ViewportPanel();
		void AssetPanel();
		void ControlPanel();
		void SceneEditorPanel();

		void OnCriticalSection_ViewportPanel();
		void OnCriticalSection_AssetPanel();
		void OnCriticalSection_ControlPanel();
		void OnCriticalSection_SceneEditorPanel();

	private:
		GLFWwindow* glfw_window = nullptr;
	};

}