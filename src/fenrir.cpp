#include <iostream>
#include <physfs.h>
#include <string.h>
#include <stdlib.h>
#include "LuaState.hpp"
#include "LuaValue.hpp"
#include "Debug.hpp"
#include "string.hpp"
#include <lua.hpp>
#include <vector>
#include "EventManager.hpp"


// The messiest of all source files :(

namespace EventManager {
	extern void init();
	extern void destroy();
	extern void poll();
}

std::vector<char*>* files = NULL;

int lua_loadFile(lua_State* l) {
	const char* name = lua_tostring(l,-1);
	lua_pop(l,-1);
	if(!PHYSFS_exists(name)) {
		return luaL_argerror(l, 1, "File does not exist"); // You fucked up, (ahahaha)
	}
	PHYSFS_File * file = PHYSFS_openRead(name);
	char* buf = new char[PHYSFS_fileLength(file)+1];
	PHYSFS_read(file, buf,1,PHYSFS_fileLength(file));
	files->push_back(buf);
	lua_pushlightuserdata(l,files->back());
	PHYSFS_close(file);
	return 1;
}
// Returns a table of all files in the dir
int lua_listDir(lua_State* l) {
	const char* name = lua_tostring(l,-1);
	lua_newtable(l);
	char **dir = PHYSFS_enumerateFiles(name);
	char **i;
	for(i=dir; *i != NULL; i++) {
		lua_pushstring(l, *i);
		lua_rawseti(l, -2, lua_objlen(l,-2)+1);
	}
	PHYSFS_freeList(dir);
	return 1; // Dat table
}

int main(int argc, char *argv[])
{
	EventManager::init();
	PHYSFS_init(argv[0]);
	// Let's init the global files vector
	files = new std::vector<char*>;
	fenrir::string toMount(PHYSFS_getBaseDir());
	toMount += PHYSFS_getDirSeparator();
	toMount += "res";
	std::cout << "stuff is " << toMount.c_str() << "\n";
	if(!PHYSFS_mount(toMount.c_str(), NULL, 1)) {
		std::cout << "Oh dear, you fucked up (trying to mount res dir): " << PHYSFS_getLastError() << std::endl;
		return 1;
	}
	// END OF BRAIN MELT
	PHYSFS_File* res = PHYSFS_openRead("/res.lua");
	if(res == NULL) {
		std::cout << "Fucked up on opening res.lua: " << PHYSFS_getLastError() << std::endl;
		return 1;
	}
	char* buf = new char[PHYSFS_fileLength(res)+1];
	PHYSFS_read(res, buf, 1, PHYSFS_fileLength(res));
	buf[PHYSFS_fileLength(res)] = '\0';
	PHYSFS_close(res);



	LuaState* baj = new LuaState();
	baj->registerFunc(lua_listDir, "listFiles");
	baj->registerFunc(lua_loadFile, "loadFile");
	baj->doString(buf);
	delete[] buf;
	delete baj;
	delete files;
	PHYSFS_deinit();
	EventManager::destroy();
	return 0;
}
