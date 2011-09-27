/*
 * Copyright 2011 The Fenrir Project. All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE FENRIR PROJECT ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FENRIR PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the authors and should not be interpreted as representing official policies, either expressed or implied, of the Fenrir Project.
*/

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
