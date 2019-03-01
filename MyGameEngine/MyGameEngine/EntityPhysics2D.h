#pragma once
#include "Physics2D.h"

#include <list>
#include <iterator>

namespace Engine {
	class EntityPhysics2D {
	public:
		void init();
		void push(Physics2D *);
		void update(double);
		void release();

		std::list<Physics2D *> list;

	private:
		std::list<Physics2D *>::iterator it;
	};
}


inline void Engine::EntityPhysics2D::init() {

}

inline void Engine::EntityPhysics2D::push(Physics2D * i_component) {
	list.push_back(i_component);
}

inline void Engine::EntityPhysics2D::update(double dt) {
	for (auto it = list.begin(); it != list.end(); ++it) {
		(*it)->update(dt);
	}
}

inline void Engine::EntityPhysics2D::release() {
	for (auto it = list.begin(); it != list.end(); ++it) {
		delete (*it);
	}
}