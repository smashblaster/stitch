#include "../context.cpp"
#include <Nintendo.h>

#ifndef SYSTEM
#define SYSTEM

class System {
	protected:
		Context* ctx;

	public:
		char* name;
		bool persistent = false;

		explicit System(Context* _ctx) {
			ctx = _ctx;
		}

		virtual ~System() {}
		virtual void init() {};
		virtual void update() {};
		void setPersistent(bool value) { persistent = value; }
};

#endif
