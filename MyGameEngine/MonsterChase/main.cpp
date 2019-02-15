#define _CRTDBG_MAP_ALLOC  
#include "Monster.h"
#include "MonsterController.h"
#include "Player.h"
#include "PlayerController.h"
#include "List.h"
#include "DebugLog.h"
#include "Allocator.h"
#include "Time.h"
#include "InputMap.h"
#include "Physics2D.h"
#include "SpriteRenderer.h"
#include "SmartPointers.h"

#include <Windows.h>
#include <crtdbg.h>  
#include <iostream>

#include "../GLib/GLib.h"

#include <conio.h>
extern bool HeapManager_UnitTest();
#include "CharacterString_UnitTest.h"

/*
int main() {
	//HeapManager_UnitTest();
	monsterchase();
	//UnitTest::CharacterString_UnitTest();
	_CrtDumpMemoryLeaks();
	return 0;
}
*/

/*
void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	//sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	sprintf_s(Buffer, lenBuffer, "VKey %d went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG

	if (i_VKeyID == 32) {
		//phy1->addForce(Vector2D<double, double>(25, 0));
	}
}
*/

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, PWSTR pCmdLine, int i_nCmdShow) {
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1200, 600);

	if (bSuccess)
	{
		Object2D * obj1 = new Object2D();
		Object2D * obj2 = new Object2D();
		Physics2D * phy1 = new Physics2D();
		Physics2D * phy2 = new Physics2D();

		phy1->pointer = obj1;
		phy2->pointer = obj2;

		Timer::Init();
		obj1->setPosition(-220, -100);
		obj2->setPosition(180, -100);

		// Create a couple of sprites using our own helper routine CreateSprite
		SpriteRenderer GoodGuy;
		GoodGuy.createSprite("..\\Assets\\data\\GoodGuy.dds");
		SpriteRenderer BadGuy;
		BadGuy.createSprite("..\\Assets\\data\\BadGuy.dds");

		//GoodGuy.obj = obj1;
		GoodGuy.pointer = phy1->pointer;
		//BadGuy.obj = obj2;
		BadGuy.pointer = phy2->pointer;



		InputMap::InitInputMap();
		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		//GLib::SetKeyStateChangeCallback(TestKeyCallback);

		bool bQuit = false;
		do
		{
			Timer::Run();

			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);
			phy1->input();

			if (!bQuit)
			{
				// IMPORTANT: Tell GLib that we want to start rendering
				GLib::BeginRendering();
				// Tell GLib that we want to render some sprites
				GLib::Sprites::BeginRendering();

				if (GoodGuy.sprite)
				{
					phy1->update(Time::dt);
					GoodGuy.update();
				}
				if (BadGuy.sprite)
				{
					// Tell GLib to render this sprite at our calculated location
					BadGuy.update();
				}

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// IMPORTANT: Tell GLib we're done rendering
				GLib::EndRendering();
			}
			InputMap::ClearInputMap();
		} while (bQuit == false);

		GoodGuy.release();
		BadGuy.release();

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();

		delete phy1;
		delete phy2;
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}
