#pragma once
#include "InputMap.h"
#include "Time.h"
#include "Object3DPointer.h"
#include "EntityMaster.h"
#include "EntityPhysics3D.h"
#include "EntitySpriteRenderer.h"
#include "Messenger.h"

namespace System {
	class Process {
	public:
		static bool BQuit;
		static void Boot();
		static void GameInit();
		static void Run();
		static void LateRun();
		static void ShutDown();
	};
}

bool System::Process::BQuit;

inline void System::Process::Boot() {
	Timer::Init();

	System::Messenger::Init();

	InputMap::Map = new std::unordered_map<unsigned int, bool>();
	InputMap::DeleteList = new std::list<unsigned int>();
	InputMap::InitInputMap();

	Engine::EntityMaster::ObjectList = new std::list<Engine::Object3DPointer *>();

	Engine::EntityPhysics3D * physic_system = new Engine::EntityPhysics3D();
	Engine::EntityMaster::Physics = physic_system;

	Engine::EntitySpriteRenderer * renderer_system = new Engine::EntitySpriteRenderer();
	Engine::EntityMaster::SRenderer = renderer_system;
}

inline void System::Process::ShutDown() {
	Engine::EntityMaster::Release();

	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();

	delete InputMap::Map;
	delete InputMap::DeleteList;

	System::Messenger::Release();
}

inline void System::Process::Run() {
	Timer::Run();
	System::Messenger::BroadCastMessages();
	GLib::Service(BQuit);
}

inline void System::Process::LateRun() {
	InputMap::ClearInputMap();
}

inline void System::Process::GameInit() {
	Engine::EntityMaster::Init();
}