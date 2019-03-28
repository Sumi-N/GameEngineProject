#define _CRTDBG_MAP_ALLOC  
#include "DebugLog.h"
#include "Allocator.h"
#include "Time.h"
#include "InputMap.h"
#include "SpriteRenderer.h"
#include "SmartPointers.h"
#include "EntityMaster.h"
#include "EntityPhysics3D.h"
#include "EntitySpriteRenderer.h"
#include "ScriptReader.h"

#include <Windows.h>
#include <crtdbg.h>  
#include <iostream>

#include "GLib.h"
#include "lua.hpp"
#include "lauxlib.h"
#include "lua.h"
#include "luaconf.h"
#include "lualib.h"


#include <conio.h>
extern bool HeapManager_UnitTest();
#include "CharacterString_UnitTest.h"
#include "Matrix4_UnitTest.h"

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, PWSTR pCmdLine, int i_nCmdShow) {

	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1200, 600);

	if (bSuccess)
	{
		Timer::Init();

		InputMap::Map = new std::unordered_map<unsigned int, bool>();
		InputMap::DeleteList = new std::list<unsigned int>();
		InputMap::InitInputMap();

		Engine::EntityMaster::Init();

		Engine::EntityPhysics3D physic_system;
		Engine::EntityMaster::Physics = &physic_system;

		Engine::EntitySpriteRenderer renderer_system;
		Engine::EntityMaster::SRenderer = &(renderer_system);

		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player1.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player2.lua");

		bool bQuit = false;
		do
		{
			Timer::Run();

			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);
			//phy1->input();

			if (!bQuit)
			{
				Engine::EntityMaster::Update(static_cast<float>(Time::dt));
			}
			InputMap::ClearInputMap();
		} while (bQuit == false);

		Engine::EntityMaster::Release();

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();

		delete InputMap::Map;
		delete InputMap::DeleteList;
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}
