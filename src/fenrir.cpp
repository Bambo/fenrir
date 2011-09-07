#include <iostream>
#include <physfs.h>
#include <string.h>
#include <stdlib.h>
#include "LuaState.hpp"
#include "LuaValue.hpp"
#include "Debug.hpp"
#include "string.hpp"
#include <lua.hpp>

/*
 * This function got a tad more complicated than anticpated
 */
int regFiles(lua_State* l) {
	lua_pushnil(l);
	while(lua_next(l, -2) != 0) {
		lua_pushnil(l);
		while(lua_next(l,-2) != 0) {
			DBGPRT(lua_tostring(l,-1))
			lua_pop(l,-1);
		}
		lua_pop(l,-2);
	}
	lua_pop(l, -2);
	return 0;
}

int main(int argc, char *argv[])
{
	PHYSFS_init(argv[0]);
	fenrir::string toMount(PHYSFS_getBaseDir());
	toMount += PHYSFS_getDirSeparator();
	toMount += "res";
	PHYSFS_mount(toMount.c_str(), NULL, 1);
	// END OF BRAIN MELT
	PHYSFS_File* res = PHYSFS_openRead("/res.lua");
	char* buf = new char[PHYSFS_fileLength(res)+1];
	PHYSFS_read(res, buf, 1, PHYSFS_fileLength(res));
	buf[PHYSFS_fileLength(res)] = '\0';
	PHYSFS_close(res);

	LuaState* baj = new LuaState();
	baj->registerFunc(regFiles, "regFiles");
	baj->doString(buf);
	delete[] buf;
	delete baj;
	PHYSFS_deinit();
	return 0;
}
