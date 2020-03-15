#pragma once

#include "Define.h"

	class ObjectHandler
	{
	public:
		ObjectHandler(Object* i_objpointer)
		{
			p = i_objpointer;
		}
		OwningPointer<Object> p;
	private:
	};

class Entity
{
public:
	static std::vector<ObjectHandler> ObjectList;
	static OwningPointer<Camera> CurrentCamera;

	static ObjectHandler Register(Object *);
	static void RegisterCamera(Camera *);
	static void Init();
	static void Update(float i_dt);
	static void CleanUp();
};