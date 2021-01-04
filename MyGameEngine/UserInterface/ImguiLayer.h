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
	void SetEventCallback(const std::function<void(Event&)> &);

private:
	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	bool OnMouseMovedEvent(MouseMovedEvent& e);
	bool OnKeyPressedEvent(KeyPressedEvent& e);
	bool OnKeyRelasedEvent(KeyReleasedEvent& e);
	bool OnWindowResizedEvent(WindowResizeEvent& e);
};
