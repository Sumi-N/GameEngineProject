#pragma once
#include "Object2D.h"
#include "EntityPhysics2D.h"
#include "EntitySpriteRenderer.h"
#include "SmartPointers.h"
#include "Object2DMaster.h"

#include <list>
#include <iterator>

namespace Engine {
	class EntityMaster {
	public:
		static std::list<Object2DMaster *> * ObjectList;
		static EntityPhysics2D * Physics;
		static EntitySpriteRenderer * SRenderer;

		static void Init();
		static void Update(double);
		static void Release();
	};
}

std::list<Engine::Object2DMaster *> * Engine::EntityMaster::ObjectList;
Engine::EntityPhysics2D * Engine::EntityMaster::Physics;
Engine::EntitySpriteRenderer * Engine::EntityMaster::SRenderer;

inline void Engine::EntityMaster::Init() {
	ObjectList = new std::list<Object2DMaster *>();
}

inline void Engine::EntityMaster::Update(double dt) {
	Physics->update(dt);
	SRenderer->update();
}

inline void Engine::EntityMaster::Release() {
	Physics->release();
	SRenderer->release();

	for (auto it = ObjectList->begin(); it != ObjectList->end(); ++it) {
		delete (*it);
	}
	delete ObjectList;
}