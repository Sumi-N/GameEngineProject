#pragma once

class Layer
{
public:
	Layer() = default;
	virtual ~Layer() = default;

	virtual void OnAttach() {};
	virtual void OnDetach() {};	
	virtual void OnUpdate(float i_delta) {};

	//virtual void OnEvent(Event& event) {}; 
};