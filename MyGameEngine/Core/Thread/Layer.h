#pragma once
#include "Define.h"

class Layer
{
public:
	Layer() = default;
	virtual ~Layer() = default;

	virtual void OnAttach() {};
	virtual void OnDetach() {};	
	virtual void OnUpdate() {};

	virtual void OnEvent(Event& event) {}; 
};