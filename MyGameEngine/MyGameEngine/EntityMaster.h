#pragma once
#include "Object3D.h"
#include "EntityPhysics3D.h"
#include "EntitySpriteRenderer.h"
#include "SmartPointers.h"
#include "Object3DPointer.h"
#include "Delegates.h"

#include <list>
#include <iterator>

namespace Engine {
	class EntityMaster {
	public:
		static std::list<Object3DPointer *> * ObjectList;
		static EntityPhysics3D * Physics;
		static EntitySpriteRenderer * SRenderer;

		static void Init();
		static void Update(float);
		static void Release();

		void testfunction(int);
		void registerfunction();

		Delegate<int> delegate;
	};
}

inline void Engine::EntityMaster::registerfunction() {
	delegate = Delegate<int>::Create<Engine::EntityMaster, &Engine::EntityMaster::testfunction>(&(*this));
	
	//test = Delegate<void *,void(int,float)>(converttovoid, &testtest);
	//test = Delegate<void *, void(int, float)>();
}

inline void Engine::EntityMaster::testfunction(int i) {
	printf("%d", i);
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
}