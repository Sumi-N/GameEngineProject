#pragma once
#include "Define.h"

#define IMGUI_IMPL_API
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <Application/Window.h>

namespace Tempest
{
	extern Window* window;

	class ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate() override;

		void Begin();
		void End();

	public:
		GLFWwindow* glfw_window = nullptr;
	};

}