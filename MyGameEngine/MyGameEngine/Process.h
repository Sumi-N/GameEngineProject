#pragma once
#include "InputMap.h"
#include "Time.h"
#include "EntityMaster.h"
#include "EntityPhysics3D.h"
#include "EntitySpriteRenderer.h"
#include "Messenger.h"

namespace System {
	class Process {
		public:
		static void Init();
		static void Quit();
	};
}

inline void System::Process::Init() {
	Timer::Init();

	System::Messenger::Init();

	InputMap::Map = new std::unordered_map<unsigned int, bool>();
	InputMap::DeleteList = new std::list<unsigned int>();
	InputMap::InitInputMap();

	Engine::EntityMaster::Init();

	Engine::EntityPhysics3D * physic_system = new Engine::EntityPhysics3D();
	Engine::EntityMaster::Physics = physic_system;

	Engine::EntitySpriteRenderer * renderer_system = new Engine::EntitySpriteRenderer();
	Engine::EntityMaster::SRenderer = renderer_system;
}

inline void System::Process::Quit() {
	Engine::EntityMaster::Release();

	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();

	delete InputMap::Map;
	delete InputMap::DeleteList;

	System::Messenger::Release();
}