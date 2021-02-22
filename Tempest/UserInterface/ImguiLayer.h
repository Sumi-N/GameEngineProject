#pragma once
#include "Define.h"

namespace Tempest
{

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
		GLFWwindow* window = nullptr;
	};

}