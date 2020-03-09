#pragma once

#include "Define.h"
#include "Object.h"

class Component
{
public:
	ObservingPointer<Object> pointer;

	virtual void Init();
	virtual void Update(float);
	virtual void CleanUp();
};

inline void Component::Init() {}

inline void Component::Update(float i_dt) {}

inline void Component::CleanUp() {}