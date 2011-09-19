#include <lua.hpp>
#include "LuaState.hpp"
#include <iostream>
#include "Debug.hpp"
#include "LuaValue.hpp"
#include <cstring>

LuaState::LuaState() {
	DBGPRT("Creating a LuaState obj " << this)
	_state = luaL_newstate();
	luaL_openlibs(_state);
}

LuaValue LuaState::getGlobalValue(const char* name) {
	return LuaValue(_state, name);
}

void LuaState::doString(const std::string& str) {
	DBGPRT("Doing " << str << "\n")
	if(luaL_loadbuffer(this->_state, str.c_str(), std::strlen(str.c_str()), "bajs") != 0) {
		DBGPRT("Fail in in syntax: " << lua_tostring(_state, -1))
	}
	if(lua_pcall(_state, 0, 0, 0) != 0) {
		DBGPRT("Runtime fail: " << lua_tostring(_state, -1))
	}

	//luaL_dostring(_state, str.c_str());
}

void LuaState::registerFunc(lua_CFunction func, const char* name) {
	lua_pushcfunction(_state, func);
	lua_setglobal(_state, name);
}

LuaState::~LuaState() {
	lua_close(_state);
}
