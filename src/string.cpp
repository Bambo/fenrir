#include "string.hpp"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <Debug.hpp>
namespace fenrir {

	string::string(const char* str) {
		int len = std::strlen(str);
		mString = new char[len+1];
		std::memcpy(mString, str, len+1);
	}

	string& string::operator+=(const string& rh) {
		DBGPRT(mString << " :::::::: " << rh.mString << "\n")
		int len = std::strlen(mString)+strlen(rh.mString);
		char* tmpStr = new char[len+1]; 
		std::memset(tmpStr, '\0', len); // Valgrind goes mad if i don't do this, needs more investigation
		std::memcpy(tmpStr, mString, std::strlen(mString));
		std::strcat(tmpStr, rh.mString);
		delete[] mString;
		mString = tmpStr;
		mString[len] = '\0';
		return *this;
	}

	string::~string() {
		delete[] mString;
	}
}
