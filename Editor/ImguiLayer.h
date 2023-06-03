#pragma once

#define IMGUI_IMPL_API
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

#include <Input/Delegate.h>
#include <Input/Input.h>
#include <Layer/Layer.h>
#include <Graphics/Define.h>
#include <Graphics/Window.h>
#include <Graphics/Device.h>
#include <Graphics/SwapChain.h>
#include <Graphics/RenderPass.h>
#include <Rendering/Framework.h>

#include "EntityInfo.h"

namespace Tempest
{
	extern Delegate<> GameThreadOnReset;
	extern Delegate<> RenderThreadOnReset;

	extern bool isEntityModifies;
	extern bool isObjectModified;
	extern int SelectedObjectIndex;
	extern EntityInfo::ComponentFlags SelectingComponent;
	extern EntityInfo::ComponentFlags SelectedObjectInfo;
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

		void FrameRender(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data);
		void FramePresent(ImGui_ImplVulkanH_Window* wd);
		void SetupVulkanWindow(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height);

	private:
		GLFWwindow* glfw_window = nullptr;
		ImGui_ImplVulkanH_Window imgui_windows_data{};
		Device graphics_device;
	};

}