#define _CRTDBG_MAP_ALLOC  
#include "DebugLog.h"
#include "Allocator.h"
#include "Time.h"
#include "InputMap.h"
#include "Physics2D.h"
#include "SpriteRenderer.h"
#include "SmartPointers.h"
#include "EntityPhysics2D.h"
#include "EntitySpriteRenderer.h"

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

	const char * filename = "..\\Assets\\editabledatas\\player.lua";
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
	lua_pop(pluastate, 1);

	int test = lua_gettop(pluastate);
	DEBUG_PRINT("the number of elements in stack is %d", test);

	lua_pushstring(pluastate, "initial_position");
	type2 = lua_gettable(pluastate, -2);
	DEBUG_PRINT("%d", type2);

	lua_pushnil(pluastate);
	lua_next(pluastate, -2);
	int hey = lua_tonumber(pluastate, -1);
	DEBUG_PRINT("%d", hey);

	lua_pop(pluastate, 1);
	lua_next(pluastate, -2);
	float hey2 = static_cast<float>(lua_tonumber(pluastate, -1));
	DEBUG_PRINT("%f", hey2);
	
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, PWSTR pCmdLine, int i_nCmdShow) {
	//yoyoyo();

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

		Engine::EntityPhysics2D::Register(phy1);
		Engine::EntityPhysics2D::Register(phy2);

		Timer::Init();
		obj1->setPosition(-220, -100);
		obj2->setPosition(180, -100);

		// Create a couple of sprites using our own helper routine CreateSprite
		SpriteRenderer GoodGuy;
		GoodGuy.createSprite("..\\Assets\\data\\GoodGuy.dds");
		SpriteRenderer BadGuy;
		BadGuy.createSprite("..\\Assets\\data\\BadGuy.dds");

		GoodGuy.pointer = phy1->pointer;
		BadGuy.pointer = phy2->pointer;

		Engine::EntitySpriteRenderer::Register(GoodGuy);
		Engine::EntitySpriteRenderer::Register(BadGuy);

		InputMap::InitInputMap();

		bool bQuit = false;
		do
		{
			Timer::Run();

			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);
			phy1->input();

			if (!bQuit)
			{
				Engine::EntityPhysics2D::Update(Time::dt);
				Engine::EntitySpriteRenderer::Update();
			}
			InputMap::ClearInputMap();
		} while (bQuit == false);

		Engine::EntitySpriteRenderer::Release();
		Engine::EntityPhysics2D::Release();

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}
