#include "LuaState.hpp"
#include "LuaValue.hpp"
#include <iostream>
#include "Debug.hpp"
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
}
#include <string>
LuaValue::LuaValue(lua_State* state, const char* name) {
	DBGPRT("Creating a fine new LuaValue, by global name")
	_state = state;
	lua_getglobal(_state, name);
	_type = lua_type(_state, -1);
	DBGPRT("_type is: " << lua_typename(_state, _type))
	_ref = luaL_ref(_state, LUA_REGISTRYINDEX);
	DBGPRT("_ref is: " << _ref)
}

LuaValue::LuaValue(lua_State* state) {
	DBGPRT("Creating a fine new LuaValue, by ref")
	_state = state;
	_type = lua_type(_state, -1);
	DBGPRT("_type is: " << lua_typename(_state, _type))
	_ref = luaL_ref(_state, LUA_REGISTRYINDEX);
	DBGPRT("_ref is: " << _ref)
}

std::string LuaValue::asString() {
	DBGPRT("LuaValue::asString() called")
	lua_rawgeti(_state, LUA_REGISTRYINDEX, _ref);
	DBGPRT("_ref is: " << _ref)
	DBGPRT("Type is: " << lua_typename(_state, lua_type(_state, -1)))
	std::string str;
	const char* cstr = lua_tostring(_state, -1);
	if(cstr == NULL) { str = ""; } else { str = cstr; }
	DBGPRT("Str is: " << str)
	lua_pop(_state, 1);
	return str;
}

bool LuaValue::isTable() {
	if(_type == LUA_TTABLE) {
		return true;
	} else {
		return false;
	}
}

// This shit is going down if this is no table...
// TODO: Add runtime debug only check, if table
LuaValue LuaValue::operator[](std::string name) {
	lua_rawgeti(_state, LUA_REGISTRYINDEX, _ref);
	lua_getfield(_state, -1, name.c_str());
	LuaValue lol(_state); 
	return lol;
}

LuaValue LuaValue::operator[](int idx) {
	lua_rawgeti(_state, LUA_REGISTRYINDEX, _ref);
	lua_pushinteger(_state, idx);
	lua_gettable(_state, -2);
	LuaValue lol(_state);
	lua_pop(_state, 1);
	return lol;
}

LuaValue::~LuaValue() {
	//luaL_unref(_state, LUA_REGISTRYINDEX, _ref);
}
