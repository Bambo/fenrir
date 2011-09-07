#include "string.hpp"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <Debug.hpp>
namespace fenrir {
	string::string(const char* str) {
		int len = std::strlen(str);
		mString = (char*)malloc(sizeof(char)*len+1);
		std::memcpy(mString, str, len);
		mString[len] = '\0';
	}

	string& string::operator+=(const string& rh) {
		int len = std::strlen(mString)+strlen(rh.mString);
		char* tmpStr = (char*)std::malloc(len+1);
		std::memcpy(tmpStr, mString, std::strlen(mString));
		std::strcat(tmpStr, rh.mString);
		free(mString);
		mString = tmpStr;
		return *this;
	}

	string::~string() {
		free(mString);
	}
}
