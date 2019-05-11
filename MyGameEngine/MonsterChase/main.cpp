#pragma once
#define _CRTDBG_MAP_ALLOC
#include "DebugLog.h"
#include "Allocator.h"
#include "Process.h"
#include "AdvancedScriptReader.h"
#include "EntityMaster.h"

#include "Player.h"
#include "PlayerPhysics.h"
#include "Monster.h"
#include "MonsterPhysics.h"
#include "CountDown.h"

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
		System::Process::Boot();

		System::AdvancedScriptReader<Player, PlayerPhysics>::CreateObject("..\\Assets\\editabledatas\\player1.lua");
		System::AdvancedScriptReader<Monster, MonsterPhysics>::CreateObject("..\\Assets\\editabledatas\\player2.lua");
		System::AdvancedScriptReader<CountDown, Physics3D>::CreateObject("..\\Assets\\editabledatas\\Timer.lua");

		System::Process::GameInit();

		do
		{
			System::Process::Run();

			if (!System::Process::BQuit)
			{
				Engine::EntityMaster::Update(static_cast<float>(Time::dt));

			}

			System::Process::LateRun();
		} while (System::Process::BQuit == false);

		System::Process::ShutDown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif
}
