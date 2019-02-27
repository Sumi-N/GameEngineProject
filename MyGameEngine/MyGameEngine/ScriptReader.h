#pragma once
#include "Object2D.h"
#include "Physics2D.h"
#include "SpriteRenderer.h"
#include "DebugLog.h"

#include "GLib.h"
#include "lua.hpp"
#include "lauxlib.h"
#include "lua.h"
#include "luaconf.h"
#include "lualib.h"

#include <assert.h>


#define FILEPTH "..\\Assets\\editabledatas\\"

namespace System {
	class ScriptReader {
	public:
		static Object2D * CreateActor(const char *);

	private:

	};
}

inline Object2D * System::ScriptReader::CreateActor(const char * i_filename) {
	lua_State * pluastate = luaL_newstate();
	assert(pluastate);
	luaL_openlibs(pluastate);

	if (luaL_loadfile(pluastate, i_filename)) {
		DEBUG_PRINT("cannot open %s\n", i_filename);
		return;
	}
	lua_pcall(pluastate, 0, 0, 0);

	//Get table
	int typecheck = lua_getglobal(pluastate, "Object2D");
	assert(typecheck == LUA_TTABLE);

	//Create Object2D
	Object2D * obj = new Object2D();

	//Get name variable
	lua_pushstring(pluastate, "name");
	typecheck = lua_gettable(pluastate, -2);
	assert(typecheck == LUA_TSTRING);
	obj->name = CharacterString(lua_tostring(pluastate, -1));
	lua_pop(pluastate, 2);

	//Get Position variable
	lua_pushstring(pluastate, "initial_position");
	typecheck = lua_gettable(pluastate, -2);
	assert(typecheck == LUA_TTABLE);

	lua_pushnil(pluastate);
	lua_next(pluastate, -2);
	double x = static_cast<double>(lua_tonumber(pluastate, -1));
	lua_pop(pluastate, 1);

	lua_next(pluastate, -2);
	double y = static_cast<double>(lua_tonumber(pluastate, -1));
	lua_pop(pluastate, 1);

	obj->setPosition(x,y);
	lua_pop(pluastate, 1);

	//Get Physics Component
	lua_pushstring(pluastate, "Physics2D_settings");
	typecheck = lua_gettable(pluastate, -2);
	if (typecheck == LUA_TTABLE) {
		//Create physics component and connect to obj
		Physics2D * phy = new Physics2D();
		phy->pointer = obj;

		//Get mass
		lua_pushstring(pluastate, "mass");
		typecheck = lua_gettable(pluastate, -2);
		assert(typecheck == LUA_TNUMBER);
		phy->mass = static_cast<double>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 2);

		//Get air friction
		lua_pushstring(pluastate, "air_friction");
		typecheck = lua_gettable(pluastate, -2);
		assert(typecheck == LUA_TNUMBER);
		phy->air_fric = static_cast<double>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 2);

		//Get velocity
		lua_pushstring(pluastate, "velocity");
		typecheck = lua_gettable(pluastate, -2);
		assert(typecheck == LUA_TTABLE);

		lua_pushnil(pluastate);
		lua_next(pluastate, -2);
		double x = static_cast<double>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		lua_next(pluastate, -2);
		double y = static_cast<double>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		phy->vel.set(Vector2D<double, double>(x, y));
		lua_pop(pluastate, 1);

		lua_pop(pluastate, 1);

		//Get acceleration
		lua_pushstring(pluastate, "acceleration");
		typecheck = lua_gettable(pluastate, -2);
		assert(typecheck == LUA_TTABLE);

		lua_pushnil(pluastate);
		lua_next(pluastate, -2);
		double x = static_cast<double>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		lua_next(pluastate, -2);
		double y = static_cast<double>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		phy->acc.set(Vector2D<double, double>(x, y));
		lua_pop(pluastate, 1);

		lua_pop(pluastate, 1);
	}
	else if (typecheck != LUA_TNIL) {
		assert(0);
	}

	lua_pushstring(pluastate, "SpriteRender_settings");
	typecheck = lua_gettable(pluastate, -2);
	if (typecheck == LUA_TTABLE) {
		SpriteRenderer srend;

		lua_pushstring(pluastate, "path");
		typecheck = lua_gettable(pluastate, -2);
		assert(typecheck == LUA_TSTRING);
		srend.createSprite(lua_tostring(pluastate, -1));
		lua_pop(pluastate, 2);

		srend.pointer = phy->pointer;
	}
	else if (typecheck != LUA_TNIL) {
		assert(0);
	}

	return obj;
}

