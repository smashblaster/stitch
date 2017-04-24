#include "../context.cpp"
#include <Nintendo.h>

#ifndef SYSTEM
#define SYSTEM

class System {
	public:
		std::string name;
		bool enabled = false;
		bool persistent = false;

		virtual ~System() {}
		virtual void init(Context *ctx) {};
		virtual void update(Context *ctx) {};
		void enable() { enabled = true; }
		void disable() { enabled = false; }
		void toggle() { enabled = !enabled; }
		void toggle(bool value) { enabled = value; }
		void setPersistent(bool value) { persistent = value; }
};

#endif
