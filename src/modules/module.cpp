#include "../context.cpp"
#include <Nintendo.h>

#ifndef MODULE
#define MODULE

class Module {
	public:
		bool enabled = true;

		virtual ~Module() {}
		virtual std::string const name() = 0;
		virtual void init(Context *ctx, CGamecubeController controller) {};
		virtual void update(Context *ctx, CGamecubeController controller) {};
};

#endif
