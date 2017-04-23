#include "../context.cpp"
#include <Nintendo.h>

#ifndef MODULE
#define MODULE

class Module {
	public:
		std::string name;
		bool enabled = true;

		virtual ~Module() {}
		virtual void init(Context *ctx, CGamecubeController controller) {};
		virtual void update(Context *ctx, CGamecubeController controller) {};
};

#endif
