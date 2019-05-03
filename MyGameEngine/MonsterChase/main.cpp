#pragma once
#define _CRTDBG_MAP_ALLOC
#include "DebugLog.h"
#include "Allocator.h"
#include "Process.h"
#include "ScriptReader.h"
#include "Messenger.h"
#include "EntityMaster.h"
#include "Physics3D.h"
#include "SmartPointers.h"
#include "EntityPhysics3D.h"
#include "Object3DPointer.h"

#include <Windows.h>
#include <crtdbg.h>  
#include <iostream>
#include <list>

//extern bool HeapManager_UnitTest();
#include "CharacterString_UnitTest.h"
#include "Matrix4_UnitTest.h"
#include "Vector3_UnitTest.h"

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, PWSTR pCmdLine, int i_nCmdShow) {

	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1200, 600);

	if (bSuccess)
	{
		System::Process::Init();

		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player1.lua");
		System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player2.lua");
		//System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player3.lua");
		//System::ScriptReader::CreateActor("..\\Assets\\editabledatas\\player4.lua");

		bool bQuit = false;

		do
		{
			Timer::Run();

			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);

			// Get player1's physics component
			std::list<Physics3D *> test = Engine::EntityMaster::Physics->getList();
			auto result = std::find_if(test.begin(), test.end(), [](Physics3D * e) {auto objpointer = e->pointer; return objpointer->name == "GoodGuy"; });

			std::string pn2 = "BadGuy";
			std::list<Engine::Object3DPointer *> test2 = *Engine::EntityMaster::ObjectList;
			auto result2 = std::find_if(test2.begin(), test2.end(), [&](Engine::Object3DPointer* e) {return e->pointer->name == "BadGuy"; });


			if (!bQuit)
			{
				Engine::EntityMaster::Update(static_cast<float>(Time::dt));

				DEBUG_PRINT("%f" (*result2)->pointer->position.x);

				if ((InputMap::Map)->at(68) == true) {
					(*result)->addForce(Vector3D(20,0,0));
				}
				else if ((InputMap::Map)->at(65) == true) {
					(*result)->addForce(Vector3D(-20, 0, 0));
				}
				else if ((InputMap::Map)->at(87) == true) {
					(*result)->addForce(Vector3D(0, 20, 0));
				}
				else if ((InputMap::Map)->at(83) == true) {
					(*result)->addForce(Vector3D(0, -20, 0));
				}

				System::Messenger::BroadCastMessages();
			}
			InputMap::ClearInputMap();
		} while (bQuit == false);

		System::Process::Quit();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}
