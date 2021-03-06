#pragma once
//#include "DebugLog.h"
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

inline void Engine::EntityMaster::Init() {
	for (auto it = ObjectList->begin(); it != ObjectList->end(); ++it) {
		(*it)->pointer->init();
	}

	Physics->init();
}