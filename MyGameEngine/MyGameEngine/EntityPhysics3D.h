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

		std::list<Physics3D*> & getList();
		
	private:
		std::list<Physics3D *> list;
	};
}

inline void Engine::EntityPhysics3D::init() {
	for (auto it = list.begin(); it != list.end(); ++it) {
		(*it)->init();
	}
}

inline void Engine::EntityPhysics3D::push(Physics3D * i_component) {
	list.push_back(i_component);
}

inline void Engine::EntityPhysics3D::update(float dt) {

	// Physics for updating collision
	for (auto it1 = list.begin(); it1 != list.end(); ++it1) {

		for (auto it2 = it1; it2 != list.end(); ++it2) {
			if (it1 == it2) continue;
			Engine::CollisionDetection::Update(dt, *it1, *it2);
		}
	}

	// Physics for updating position
	for (auto it = list.begin(); it != list.end(); ++it) {
		(*it)->update(dt);
	}
}

inline void Engine::EntityPhysics3D::release() {
	for (auto it = list.begin(); it != list.end(); ++it) {
		delete (*it);
	}
}

inline std::list<Physics3D*> & Engine::EntityPhysics3D::getList()
{
	return list;
}
