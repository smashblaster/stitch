#include "../context.cpp"
#include <Nintendo.h>

#ifndef SYSTEM
#define SYSTEM

class System {
	public:
		std::string name;
		bool persistent = false;
		bool enabled = true;

		virtual ~System() {}
		virtual void init(Context *ctx, CGamecubeController controller) {};
		virtual void update(Context *ctx, CGamecubeController controller) {};
		void enable() { enabled = true; }
		void disable() { enabled = false; }
		void toggle() { enabled = !enabled; }
		void setPersistent(bool value) { persistent = value; }
};

#endif
