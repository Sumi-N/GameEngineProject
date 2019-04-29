#pragma once
#include "DebugLog.h"
#include "Object3D.h"
#include "EntityPhysics3D.h"
#include "EntitySpriteRenderer.h"
#include "SmartPointers.h"
#include "Object3DPointer.h"
#include "Delegates.h"

#include <list>
#include <iterator>
#include <string>

namespace Engine {
	class EntityMaster {
	public:
		static std::list<Object3DPointer *> * ObjectList;
		static EntityPhysics3D * Physics;
		static EntitySpriteRenderer * SRenderer;

		static void Init();
		static void Update(float);
		static void Release();
	};
}

std::list<Engine::Object3DPointer *> * Engine::EntityMaster::ObjectList;
Engine::EntityPhysics3D * Engine::EntityMaster::Physics;
Engine::EntitySpriteRenderer * Engine::EntityMaster::SRenderer;

inline void Engine::EntityMaster::Init() {
	ObjectList = new std::list<Object3DPointer *>();
}

inline void Engine::EntityMaster::Update(float dt) {
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
	delete Physics;
	delete SRenderer;
}