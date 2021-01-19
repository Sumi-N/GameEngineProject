#pragma once
#include "ScriptReader.h"
#include "Physics3D.h"
#include "SpriteRenderer.h"

//#include "GLib.h"
#include "lua.hpp"
#include "lauxlib.h"
#include "lua.h"
#include "luaconf.h"
#include "lualib.h"

namespace System {
		template <class ObjectDerived, class PhysicsDerived> class AdvancedScriptReader
		{
		public:
			static Object3D * CreateObject(const char * i_filename);
		};
}

template<class ObjectDerived, class PhysicsDerived>
inline Object3D * System::AdvancedScriptReader<ObjectDerived, PhysicsDerived>::CreateObject(const char * i_filename)
{
	lua_State * pluastate = luaL_newstate();
	assert(pluastate);
	luaL_openlibs(pluastate);

	if (luaL_loadfile(pluastate, i_filename)) {
		DEBUG_PRINT("cannot open %s\n", i_filename);
		assert(0);
	}
	lua_pcall(pluastate, 0, 0, 0);

	//Get table
	int typecheck = lua_getglobal(pluastate, "Object3D");
	assert(typecheck == LUA_TTABLE);

	//Create Object3D
	Object3D * obj = new ObjectDerived();
	Engine::Object3DPointer * objp = new Engine::Object3DPointer();
	objp->pointer = obj;
	Engine::EntityMaster::ObjectList->push_back(objp);

	//Get name variable
	lua_pushstring(pluastate, "name");
	typecheck = lua_gettable(pluastate, -2);
	assert(typecheck == LUA_TSTRING);
	//DEBUG_PRINT("%s", lua_tostring(pluastate, -1));
	obj->name = std::string(lua_tostring(pluastate, -1));
	//DEBUG_PRINT("%s", obj->name);
	lua_pop(pluastate, 1);

	//Get Position variable
	lua_pushstring(pluastate, "initial_position");
	typecheck = lua_gettable(pluastate, -2);
	assert(typecheck == LUA_TTABLE);

	lua_pushnil(pluastate);
	lua_next(pluastate, -2);
	float x = static_cast<float>(lua_tonumber(pluastate, -1));
	lua_pop(pluastate, 1);

	lua_next(pluastate, -2);
	float y = static_cast<float>(lua_tonumber(pluastate, -1));
	lua_pop(pluastate, 1);

	lua_next(pluastate, -2);
	float z = static_cast<float>(lua_tonumber(pluastate, -1));
	lua_pop(pluastate, 1);

	obj->pos.Set(x, y, z);
	lua_pop(pluastate, 2);

	//Get Rotation variable
	lua_pushstring(pluastate, "initial_rotation");
	typecheck = lua_gettable(pluastate, -2);
	assert(typecheck == LUA_TTABLE);

	lua_pushnil(pluastate);
	lua_next(pluastate, -2);
	float roll = static_cast<float>(lua_tonumber(pluastate, -1));
	lua_pop(pluastate, 1);

	lua_next(pluastate, -2);
	float pitch = static_cast<float>(lua_tonumber(pluastate, -1));
	lua_pop(pluastate, 1);

	lua_next(pluastate, -2);
	float yaw = static_cast<float>(lua_tonumber(pluastate, -1));
	lua_pop(pluastate, 1);

	obj->rot.Set(roll, pitch, yaw);
	lua_pop(pluastate, 2);

	//Get Physics Component
	lua_pushstring(pluastate, "Physics2D_settings");
	typecheck = lua_gettable(pluastate, -2);
	if (typecheck == LUA_TTABLE) {
		//Create physics component and connect to obj
		Physics3D * phy = new PhysicsDerived();
		phy->pointer = objp->pointer;
		Engine::EntityMaster::Physics->push(phy);
		//Get mass
		lua_pushstring(pluastate, "mass");
		typecheck = lua_gettable(pluastate, -2);
		assert(typecheck == LUA_TNUMBER);
		phy->mass = static_cast<float>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		//Get air friction
		lua_pushstring(pluastate, "air_friction");
		typecheck = lua_gettable(pluastate, -2);
		assert(typecheck == LUA_TNUMBER);
		phy->air_fric = static_cast<float>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		//Get velocity
		lua_pushstring(pluastate, "velocity");
		typecheck = lua_gettable(pluastate, -2);
		assert(typecheck == LUA_TTABLE);

		lua_pushnil(pluastate);
		lua_next(pluastate, -2);
		float vel_x = static_cast<float>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		lua_next(pluastate, -2);
		float vel_y = static_cast<float>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		lua_next(pluastate, -2);
		float vel_z = static_cast<float>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		phy->vel.Set(vel_x, vel_y, vel_z);
		lua_pop(pluastate, 1);

		lua_pop(pluastate, 1);

		//Get acceleration
		lua_pushstring(pluastate, "accelaration");
		typecheck = lua_gettable(pluastate, -2);
		assert(typecheck == LUA_TTABLE);

		lua_pushnil(pluastate);
		lua_next(pluastate, -2);
		float acc_x = static_cast<float>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		lua_next(pluastate, -2);
		float acc_y = static_cast<float>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		lua_next(pluastate, -2);
		float acc_z = static_cast<float>(lua_tonumber(pluastate, -1));
		lua_pop(pluastate, 1);

		phy->acc.Set(acc_x, acc_y, acc_z);
		lua_pop(pluastate, 1);

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
		const char * path = lua_tostring(pluastate, -1);
		if (path != "") {
			srend.createSprite(path);
			lua_pop(pluastate, 2);

			srend.pointer = objp->pointer;
			Engine::EntityMaster::SRenderer->push(srend);
			// Just for temporal solution, pass the AABB information
			srend.PassAABBInfo();
		}
	}
	else if (typecheck != LUA_TNIL) {
		assert(0);
	}

	lua_close(pluastate);

	return obj;
}
