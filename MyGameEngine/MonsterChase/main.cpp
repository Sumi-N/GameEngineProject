#pragma once
#define _CRTDBG_MAP_ALLOC
#include "DebugLog.h"
#include "Allocator.h"
#include "Process.h"
#include "ScriptReader.h"
#include "EntityMaster.h"
#include "Physics3D.h"
#include "SmartPointers.h"
#include "EntityPhysics3D.h"

#include <Windows.h>
#include <crtdbg.h>  
#include <iostream>
#include <list>

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
		System::Process::Init();

		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player1.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player2.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player3.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player4.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player1.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player2.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player3.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player4.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player1.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player2.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player3.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player4.lua");

		bool bQuit = false;

		do
		{
			Timer::Run();

			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);

			if (!bQuit)
			{
				Engine::EntityMaster::Update(static_cast<float>(Time::dt));

				if ((InputMap::Map)->at(32) == true) {
					std::string pn = "player1";
					std::list<Physics3D *> test = Engine::EntityMaster::Physics->getList();
					auto result = std::find_if(test.begin(), test.end(), [](Physics3D * e) {auto objpointer = e->pointer; return objpointer->name == "GoodGuy"; });
					(*result)->addForce(Vector3D(-1,0,0));
				}
			}
			InputMap::ClearInputMap();
		} while (bQuit == false);

		System::Process::Quit();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}
