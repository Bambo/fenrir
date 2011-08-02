#include <iostream>
#include <physfs.h>
#include <string.h>
#include <stdlib.h>
#include "LuaState.hpp"
#include "LuaValue.hpp"
#include <string>
int main(int argc, char *argv[])
{
	PHYSFS_init(argv[0]);
	std::string toMount;
	toMount = PHYSFS_getBaseDir();
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
	baj->doString(buf);
	LuaValue apa = baj->getGlobalValue("apa");
	std::cout << apa[1][1][1].asString();
	delete[] buf;
	delete baj;
	PHYSFS_deinit();
	return 0;
}
