#ifndef _DEBUG_H
#define _DEBUG_H
#ifdef __DEBUG
	#define DBGPRT(x) DBGPRT2(x)
	#define DBGPRT2(x) std::cout << "DEBUG(" << __FILE__ << ":"<< __LINE__ <<"): " << x << std::endl;
#else
	#define DBGPRT(x)
#endif
#endif
