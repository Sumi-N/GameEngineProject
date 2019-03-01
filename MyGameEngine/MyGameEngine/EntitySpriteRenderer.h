#pragma once
#include "SpriteRenderer.h"

#include <list>
#include <iterator>

namespace Engine {
	class EntitySpriteRenderer {
	public:
		void init();
		void push(SpriteRenderer &);
		void update();
		void release();

	private:
		std::list<SpriteRenderer> list;
		std::list<SpriteRenderer>::iterator it;
	};
}

inline void Engine::EntitySpriteRenderer::init() {

}

inline void Engine::EntitySpriteRenderer::push(SpriteRenderer & i_component)
{
	list.push_back(i_component);
}

inline void Engine::EntitySpriteRenderer::update()
{
	// IMPORTANT: Tell GLib that we want to start rendering
	GLib::BeginRendering();
	// Tell GLib that we want to render some sprites
	GLib::Sprites::BeginRendering();

	for (auto it = list.begin(); it != list.end(); ++it) {
		if ((*it).sprite) {
			(*it).update();
		}

	}

	// Tell GLib we're done rendering sprites
	GLib::Sprites::EndRendering();
	// IMPORTANT: Tell GLib we're done rendering
	GLib::EndRendering();
}

inline void Engine::EntitySpriteRenderer::release()
{
	for (auto it = list.begin(); it != list.end(); ++it) {
		if ((*it).sprite) {
			(*it).release();
		}
	}
}
