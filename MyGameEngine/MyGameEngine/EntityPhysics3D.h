#pragma once
#include "Physics3D.h"

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
	for (auto it = list.begin(); it != list.end(); ++it) {
		(*it)->update(dt);
	}
}

inline void Engine::EntityPhysics3D::release() {
	for (auto it = list.begin(); it != list.end(); ++it) {
		delete (*it);
	}
}