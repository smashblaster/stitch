#include "../context.hpp"

#pragma once

class System {
	protected:
		Context* ctx;

	public:
		char* name;
		bool enabled = false;
		bool persistent = false;

		explicit System(Context* _ctx) {
			ctx = _ctx;
		}

		virtual ~System() {}
		virtual void init() {}
		virtual void update() {}
		void enable() { enabled = true; }
		void disable() { enabled = false; }
		void toggle() { enabled = !enabled; }
		void toggle(bool value) { enabled = value; }
		void setPersistent(bool value) { persistent = value; }
};
