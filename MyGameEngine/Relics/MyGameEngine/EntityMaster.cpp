#pragma once

#include "EntityMaster.h"

std::list<Engine::Object3DPointer *> * Engine::EntityMaster::ObjectList;
Engine::EntityPhysics3D * Engine::EntityMaster::Physics;
Engine::EntitySpriteRenderer * Engine::EntityMaster::SRenderer;

void Engine::EntityMaster::Release() {
	Physics->release();
	SRenderer->release();

	for (auto it = ObjectList->begin(); it != ObjectList->end(); ++it) {
		delete (*it);
	}
	delete ObjectList;
	delete Physics;
	delete SRenderer;
}

void Engine::EntityMaster::Update(float dt) {
	Physics->update(dt);
	SRenderer->update();

	for (auto it = ObjectList->begin(); it != ObjectList->end(); ++it) {
		(*it)->pointer->update();
	}
}