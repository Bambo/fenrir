extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
}
#include "LuaState.hpp"
#include <iostream>
#include "Debug.hpp"
#include "LuaValue.hpp"

LuaState::LuaState() {
	DBGPRT("Creating a LuaState obj " << this)
	_state = luaL_newstate();
}

LuaValue LuaState::getGlobalValue(const char* name) {
	return LuaValue(_state, name);
}

void LuaState::doString(const std::string& str) {
	DBGPRT("Doing " << str << "\n")
	luaL_dostring(_state, str.c_str());
}

void LuaState::registerFunc(lua_CFunction func, const char* name) {
	lua_pushcfunction(_state, func);
	lua_setglobal(_state, name);
}

LuaState::~LuaState() {
	lua_close(_state);
}
