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

#include "GLib.h"
#include "lua.hpp"
#include "lauxlib.h"
#include "lua.h"
#include "luaconf.h"
#include "lualib.h"


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

void yoyoyo() {
	lua_State * pluastate = luaL_newstate();
	assert(pluastate);
	luaL_openlibs(pluastate);

	size_t sizefile = 0;
	const char * filename = "..\\assets\\editabledatas\\player.lua";
	//uint8_t * pfilecontents = loadfile("..\\assets\\editabledatas\\player.lua");
	if (luaL_loadfile(pluastate, filename)) {
		fprintf(stderr, "cannot open %s\n", filename);
		return;
	}
	lua_pcall(pluastate, 0, 0, 0);

	int type = lua_getglobal(pluastate, "Player");
	assert(type == LUA_TTABLE);

	lua_pushstring(pluastate, "name");
	int type2 = lua_gettable(pluastate, -2);
	assert(type2 == LUA_TSTRING);
	const char * pName = lua_tostring(pluastate, -1);
	DEBUG_PRINT("%s",pName);
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, PWSTR pCmdLine, int i_nCmdShow) {
	yoyoyo();

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
