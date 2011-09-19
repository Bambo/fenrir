#include "string.hpp"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <Debug.hpp>
namespace fenrir {
	string::string(const char* str) {
		if(mString == NULL) {
			DBGPRT("is null ")
		} else {
			DBGPRT("not null")
		}
		int len = std::strlen(str);
		mString = (char*)malloc(sizeof(char)*len+1);
		std::memcpy(mString, str, len);
		mString[len] = '\0';
		DBGPRT("String is now " << mString)
	}

	string& string::operator+=(const string& rh) {
		int len = std::strlen(mString)+strlen(rh.mString);
		char* tmpStr = (char*)std::malloc(len-1); // One less zero since we combine ;)
		std::memcpy(tmpStr, mString, std::strlen(mString));
		std::strcat(tmpStr, rh.mString);
		tmpStr[len-1] = '\0';
		free(mString);
		mString = tmpStr;
		DBGPRT("String is naow " << mString)
		return *this;
	}

	string::~string() {
		DBGPRT("NOW DELETING " << mString)
		free(mString);
	}
}
