#include "IResource.hpp"
#include <stdint.h>
extern "C" { // Lua no do this :(
#include <lua.h>
}

class LuaResource : IResource {
public:
	static uint8_t type;
	wchar_t* name;
	LuaResource();
};
