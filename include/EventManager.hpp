typedef void(eventCallback)(void*);
namespace EventManager {
	int getId(); // Very unexpensive to call.
	void registerEvent(int id, eventCallback* event);
	void event(int id, void* data);
	// The 3 functions below are only called by the main function. (do not call btw)
	//void init(); // Call first
	//void destroy(); // Call when done
	//void poll();
}
