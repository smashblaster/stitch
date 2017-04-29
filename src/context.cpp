#include "context.hpp"
#include "systems/system.hpp"

uint8_t Context::get(std::string button, Gamecube_Report_t state) {
	if (button == "a") return state.a;
	if (button == "b") return state.b;
	if (button == "x") return state.x;
	if (button == "y") return state.y;
	if (button == "l") return state.l;
	if (button == "r") return state.r;
	if (button == "z") return state.z;
	if (button == "start") return state.start;
	if (button == "ddown") return state.ddown;
	if (button == "dleft") return state.dleft;
	if (button == "dright") return state.dright;
	if (button == "dup") return state.dup;
	if (button == "cxAxis") return state.cxAxis;
	if (button == "cyAxis") return state.cyAxis;
	if (button == "left") return state.left;
	if (button == "right") return state.right;
	if (button == "xAxis") return state.xAxis;
	if (button == "yAxis") return state.yAxis;
	return 0;
}

void Context::set(std::string button, uint8_t value) {
	if (button == "a") data.report.a = value;
	if (button == "b") data.report.b = value;
	if (button == "x") data.report.x = value;
	if (button == "y") data.report.y = value;
	if (button == "l") data.report.l = value;
	if (button == "r") data.report.r = value;
	if (button == "z") data.report.z = value;
	if (button == "start") data.report.start = value;
	if (button == "ddown") data.report.ddown = value;
	if (button == "dleft") data.report.dleft = value;
	if (button == "dright") data.report.dright = value;
	if (button == "dup") data.report.dup = value;
	if (button == "cxAxis") data.report.cxAxis = value;
	if (button == "cyAxis") data.report.cyAxis = value;
	if (button == "left") data.report.left = value;
	if (button == "right") data.report.right = value;
	if (button == "xAxis") data.report.xAxis = value;
	if (button == "yAxis") data.report.yAxis = value;
}

bool Context::pressed(std::string button) {
	return std::find(pressedButtons.begin(), pressedButtons.end(), button) != pressedButtons.end();
}

bool Context::released(std::string button) {
	return std::find(releasedButtons.begin(), releasedButtons.end(), button) != releasedButtons.end();
}

System* Context::getSystem(std::string name) {
	for (auto &system : systems) {
		if (system->name == name) return system;
	}
}

void Context::addSystem(char* name, System* system, bool persistent, bool enabled) {
	enabled = persistent || enabled;
	system->name = name;
	system->toggle(enabled);
	system->setPersistent(persistent);
	systems.push_back(system);
}

void Context::toggleSystem(std::string name) {
	System* system = getSystem(name);
	toggleSystem(system, !system->enabled);
}

void Context::toggleSystem(std::string name, bool value) {
	System* system = getSystem(name);
	toggleSystem(system, value);
}

void Context::toggleSystem(System* system) { system->enabled = !system->enabled; }
void Context::toggleSystem(System* system, bool value) { system->enabled = value; }
