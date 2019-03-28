#pragma once
#include "Physics3D.h"
#include "CollisionDetection.h"

#include <list>
#include <iterator>

namespace Engine {
	class EntityPhysics3D {
	public:
		void init();
		void push(Physics3D *);
		void update(float);
		void release();
		
	private:
		std::list<Physics3D *> list;
	};
}

inline void Engine::EntityPhysics3D::init() {

}

inline void Engine::EntityPhysics3D::push(Physics3D * i_component) {
	list.push_back(i_component);
}

inline void Engine::EntityPhysics3D::update(float dt) {
	// Physics for velocity
	for (auto it = list.begin(); it != list.end(); ++it) {
		(*it)->update(dt);
	}

	// Physics for collision
	for (auto it1 = list.begin(); it1 != list.end(); ++it1) {
		for (auto it2 = it1; it2 != list.end(); ++it2) {
			if (it1 == it2) continue;
			Engine::CollisionDetection::For2D(*it1, *it2);
		}
	}
}

inline void Engine::EntityPhysics3D::release() {
	for (auto it = list.begin(); it != list.end(); ++it) {
		delete (*it);
	}
}
