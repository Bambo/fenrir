/*
 * Copyright 2011 The Fenrir Project. All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE FENRIR PROJECT ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FENRIR PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the authors and should not be interpreted as representing official policies, either expressed or implied, of the Fenrir Project.
*/

#define LUA_USE_APICHECK
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
	DBGPRT("HERE HERE")
	DBGPRT("Creating a fine new LuaValue, by global name")
	_state = state;
	lua_getglobal(_state, name);
	_type = lua_type(_state, -1);
	DBGPRT("_type is: " << lua_typename(_state, _type))
	_ref = luaL_ref(_state, LUA_REGISTRYINDEX);
	DBGPRT("_ref is: " << _ref)
	_refCount = new int(1);
	DBGPRT("LuaV is " << this << "\n")
}

LuaValue::LuaValue(lua_State* state) {
	// When this is called, we are assuming that the reference is already pushed on the stack
	DBGPRT("Creating a fine new LuaValue, by ref")
	_state = state;
	_type = lua_type(_state, -1);
	DBGPRT("_type is: " << lua_typename(_state, _type))
	_ref = luaL_ref(_state, LUA_REGISTRYINDEX);
	DBGPRT("_ref is: " << _ref)
	_refCount = new int(1);
	DBGPRT("_refCount is now " << *_refCount << "\n")
	DBGPRT("LuaV is " << this << "\n")
}

LuaValue::LuaValue(const LuaValue& old) {
	_ref = old._ref;
	_state = old._state;
	_type = old._type;
	_refCount = old._refCount;
	*_refCount = *_refCount + 1;
	DBGPRT("I'm in new copy\n_ref is " << _ref << "\n_refCount is " << *_refCount << "\n")
}

std::string LuaValue::asString() {
	DBGPRT("LuaValue::asString() called")
	lua_rawgeti(_state, LUA_REGISTRYINDEX, _ref);
	DBGPRT("_ref is: " << _ref)
	DBGPRT("Type is: " << lua_typename(_state, lua_type(_state, -1)))
	const char* cstr = lua_tostring(_state, -1);
	DBGPRT("cstr is: " << cstr)
	lua_pop(_state, 1);
	return cstr;
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
	lua_pushstring(_state, name.c_str());
	lua_gettable(_state, -2);
	LuaValue lol(_state);
	DBGPRT("now leaving []")
	return lol;
}

LuaValue LuaValue::operator[](unsigned int idx) {
	DBGPRT("Now entering []")
	lua_rawgeti(_state, LUA_REGISTRYINDEX, _ref);
	lua_pushinteger(_state, idx);
	lua_gettable(_state, -2);
	LuaValue lol(_state); // Pops the value
	lua_pop(_state, 1); // We pop the table
	DBGPRT("Now leaving []")
	return lol;
}

LuaValue::~LuaValue() {
	DBGPRT("Removing LuaValue " << this << " with _ref " << _ref << "\n")
	*_refCount = *_refCount - 1;
	DBGPRT("_refCount is " << *_refCount << "\n")
	if(*_refCount == 0)
		luaL_unref(_state, LUA_REGISTRYINDEX, _ref);
		DBGPRT("Deleting refcount\n")
		delete _refCount;


}
