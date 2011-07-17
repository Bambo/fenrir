#ifndef _DEBUG_H
#define _DEBUG_H
#ifdef __DEBUG
	#define DBGPRT(x) std::cout << "DEBUG: " << x << std::endl;
#else
	#define DBGPRT(x)
#endif
#endif
