#pragma once
#include "SpriteRenderer.h"

#include <list>
#include <iterator>

namespace Engine {
	class EntitySpriteRenderer {
	public:
		static void Init();
		static void Register(SpriteRenderer &);
		static void Update();
		static void Release();

	private:
		static std::list<SpriteRenderer> list;
		static std::list<SpriteRenderer>::iterator it;
	};
}

std::list<SpriteRenderer> Engine::EntitySpriteRenderer::list;
std::list<SpriteRenderer>::iterator Engine::EntitySpriteRenderer::it;

inline void Engine::EntitySpriteRenderer::Init() {

}

inline void Engine::EntitySpriteRenderer::Register(SpriteRenderer & i_component)
{
	list.push_back(i_component);
}

inline void Engine::EntitySpriteRenderer::Update()
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

inline void Engine::EntitySpriteRenderer::Release()
{
	for (auto it = list.begin(); it != list.end(); ++it) {
		if ((*it).sprite) {
			(*it).release();
		}
	}
}
