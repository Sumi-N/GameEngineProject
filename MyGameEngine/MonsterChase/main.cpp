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

		// Get components
		std::list<Physics3D *> phy_list = Engine::EntityMaster::Physics->getList();
		auto phy_player = std::find_if(phy_list.begin(), phy_list.end(), [](Physics3D * e) {auto objpointer = e->pointer; return objpointer->name == "GoodGuy"; });

		std::list<Engine::Object3DPointer *> obj_list = *Engine::EntityMaster::ObjectList;
		auto obj_enemy = std::find_if(obj_list.begin(), obj_list.end(), [&](Engine::Object3DPointer* e) {return e->pointer->name == "BadGuy"; });
		auto obj_player = std::find_if(obj_list.begin(), obj_list.end(), [&](Engine::Object3DPointer* e) {return e->pointer->name == "GoodGuy"; });

		float timer = 0.0f;

		do
		{
			Timer::Run();

			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);

			if (!bQuit)
			{
				Engine::EntityMaster::Update(static_cast<float>(Time::dt));

				timer += static_cast<float>(Time::dt);
				if (timer < 10000) {
					DEBUG_PRINT("%f", timer/1000);
				}

				Vector3D pos_player = (*obj_player)->pointer->pos;
				Vector3D pos_enemy = (*obj_enemy)->pointer->pos;
				
				if (pos_enemy.x >= pos_player.x) {
					(*obj_enemy)->pointer->pos.x -= 0.01f;
				}
				else {
					(*obj_enemy)->pointer->pos.x += 0.01f;
				}

				if (pos_enemy.y >= pos_player.y) {
					(*obj_enemy)->pointer->pos.y -= 0.01f;
				}
				else {
					(*obj_enemy)->pointer->pos.y += 0.01f;
				}

				if ((InputMap::Map)->at(68) == true) {
					(*phy_player)->addForce(Vector3D(20,0,0));
					//DEBUG_PRINT("right");
				}
				else if ((InputMap::Map)->at(65) == true) {
					(*phy_player)->addForce(Vector3D(-20, 0, 0));
					//DEBUG_PRINT("left", timer);
				}
				else if ((InputMap::Map)->at(87) == true) {
					(*phy_player)->addForce(Vector3D(0, 20, 0));
					//DEBUG_PRINT("up", timer);
				}
				else if ((InputMap::Map)->at(83) == true) {
					(*phy_player)->addForce(Vector3D(0, -20, 0));
					//DEBUG_PRINT("down", timer);
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
