#pragma once
#include "Physics2D.h"

#include <list>
#include <iterator>

namespace Engine {
	class EntityPhysics2D {
	public:
		static void Init();
		static void Register(Physics2D *);
		static void Update(double);
		static void Release();

	private:
		static std::list<Physics2D *> list;
		static std::list<Physics2D *>::iterator it;
	};
}

std::list<Physics2D*> Engine::EntityPhysics2D::list;
std::list<Physics2D*>::iterator Engine::EntityPhysics2D::it;

inline void Engine::EntityPhysics2D::Init() {

}

inline void Engine::EntityPhysics2D::Register(Physics2D * i_component) {
	list.push_back(i_component);
}

inline void Engine::EntityPhysics2D::Update(double dt) {
	for (auto it = list.begin(); it != list.end(); ++it) {
		(*it)->update(dt);
	}
}

inline void Engine::EntityPhysics2D::Release() {
	for (auto it = list.begin(); it != list.end(); ++it) {
		delete (*it);
	}
}