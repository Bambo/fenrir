#ifndef _LUASTATE_H
#define _LUASTATE_H
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
}
#include "LuaValue.hpp"

class LuaState {
private:
	lua_State* _state;
public:
	LuaState();
	void doString(const std::string&);
	LuaValue getGlobalValue(const char* name);
	~LuaState();
};
#endif
