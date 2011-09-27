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
		_event* ev = new _event{id, event}; //Initalizer list from c++11
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
		// Range-based for loop, introduced in c++11.
		for(_event* ev : *events) {
			std::cout << ev->id << "\n";
			ev->callback((void*)"troll");
		}
		events->clear();
	}
}
