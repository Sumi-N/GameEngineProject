#pragma once
#include "Define.h"
#include "imgui_impl_opengl3.h"

class ImguiLayer : public Layer
{
public:
	ImguiLayer();
	~ImguiLayer();

	void OnAttach();
	void OnDetach();

	void OnUpdate() override;
	void OnEvent(Event& event) override;
};
