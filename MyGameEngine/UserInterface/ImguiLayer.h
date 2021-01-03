#pragma once
#include "Define.h"

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
