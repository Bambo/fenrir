#ifndef _LUAVALUE_HPP
#define _LUAVALUE_HPP
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
}
#include "LuaState.hpp"
#include <string>
class LuaValue {
friend class LuaState;
private:
	int _ref; // Lua reference
	lua_State* _state; // Lua state
	int* _refCount;
	int _type;
	LuaValue(lua_State* state, const char* name);
	LuaValue(lua_State* state);
public:
	LuaValue(const LuaValue&);
	std::string asString();
	bool isTable();
	LuaValue operator[](std::string);
	LuaValue operator[](unsigned int);
	~LuaValue();
};

#endif
