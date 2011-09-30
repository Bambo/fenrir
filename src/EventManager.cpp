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
#include "EventManager.hpp"
#include <iostream>
#include <vector>
// Doing it in under 40 lines ;)
typedef struct {
	int id;
	eventCallback* callback;
} _event;
static std::vector<_event*>* events; // This is secret stuff
static int lastId = 0;

namespace EventManager {
	int getId() {
		return ++lastId;
	}
	void registerEvent(int id, eventCallback* event) {
		std::cout << "Regging naow\n";
		_event* ev = new _event;
		ev->id = id;
		ev->callback = event;
		events->push_back(ev);
	}
	void init() {
		events = new std::vector<_event*>;
	}
	void destroy() {
		std::cout << "BAI\n";
		delete events; // No fuckups here, tada
	}
	void poll() {
		auto it = events->front();
		auto end = events->back();
		for(; it != end; it++) {
			it->callback((void*)"troll");
		}
		events->clear();
	}
}
