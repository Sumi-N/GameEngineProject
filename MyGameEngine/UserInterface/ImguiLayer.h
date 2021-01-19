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

private:
	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	bool OnMouseMovedEvent(MouseMovedEvent& e);
	bool OnKeyPressedEvent(KeyPressedEvent& e);
	bool OnKeyRelasedEvent(KeyReleasedEvent& e);
	bool OnWindowResizedEvent(WindowResizeEvent& e);

private:
	ofbx::IScene* g_scene = nullptr;
	const ofbx::IElement* g_selected_element = nullptr;
	const ofbx::Object* g_selected_object = nullptr;

	void onGUI();
	void showObjectsGUI(const ofbx::IScene&);
	void showObjectGUI(const ofbx::Object&);
	static void showCurveGUI(const ofbx::Object&);
	void showGUI(ofbx::IElementProperty&);

	template <typename T>
	void showArray(const char*, const char*, ofbx::IElementProperty&);
	void showGUI(const ofbx::IElement&);
	template <int N>
	void catProperty(char(&out)[N], const ofbx::IElementProperty&);
	int getPropertyCount(ofbx::IElementProperty*);
	template <int N>
	void toString(ofbx::DataView view, char(&out)[N]);
};
