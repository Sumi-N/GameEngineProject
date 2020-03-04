#pragma once

#include "Define.h"

	class ObjectHandler
	{
	public:
		OwningPointer<Object> p;
	private:
	};

class Entity
{
public:
	static std::vector<ObjectHandler> ObjectList;

	static void Init();
	static void Update(float i_dt);
	static void CleanUp();
};