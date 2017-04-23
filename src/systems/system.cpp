#include "../context.cpp"
#include <Nintendo.h>

#ifndef SYSTEM
#define SYSTEM

class System {
	public:
		std::string name;
		bool enabled = true;

		virtual ~System() {}
		virtual void init(Context *ctx, CGamecubeController controller) {};
		virtual void update(Context *ctx, CGamecubeController controller) {};
};

#endif
