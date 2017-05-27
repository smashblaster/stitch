#include "context.hpp"
#include "systems/system.hpp"

uint8_t Context::get(std::string button, Gamecube_Report_t state) {
	if (button == "A") return state.a;
	if (button == "B") return state.b;
	if (button == "X") return state.x;
	if (button == "Y") return state.y;
	if (button == "L") return state.l;
	if (button == "R") return state.r;
	if (button == "Z") return state.z;
	if (button == "START") return state.start;
	if (button == "DDOWN") return state.ddown;
	if (button == "DLEFT") return state.dleft;
	if (button == "DRIGHT") return state.dright;
	if (button == "DUP") return state.dup;
	if (button == "CXAXIS") return state.cxAxis;
	if (button == "CYAXIS") return state.cyAxis;
	if (button == "LEFT") return state.left;
	if (button == "RIGHT") return state.right;
	if (button == "XAXIS") return state.xAxis;
	if (button == "YAXIS") return state.yAxis;
	return 0;
}

void Context::set(std::string button, uint8_t value) {
	if (button == "A") data.report.a = value;
	if (button == "B") data.report.b = value;
	if (button == "X") data.report.x = value;
	if (button == "Y") data.report.y = value;
	if (button == "L") data.report.l = value;
	if (button == "R") data.report.r = value;
	if (button == "Z") data.report.z = value;
	if (button == "START") data.report.start = value;
	if (button == "DDOWN") data.report.ddown = value;
	if (button == "DLEFT") data.report.dleft = value;
	if (button == "DRIGHT") data.report.dright = value;
	if (button == "DUP") data.report.dup = value;
	if (button == "CXAXIS") data.report.cxAxis = value;
	if (button == "CYAXIS") data.report.cyAxis = value;
	if (button == "LEFT") data.report.left = value;
	if (button == "RIGHT") data.report.right = value;
	if (button == "XAXIS") data.report.xAxis = value;
	if (button == "YAXIS") data.report.yAxis = value;
}

bool Context::pressed(std::string button) {
	return std::find(pressedButtons.begin(), pressedButtons.end(), button) != pressedButtons.end();
}

// bool Context::released(std::string button) {
// 	return std::find(releasedButtons.begin(), releasedButtons.end(), button) != releasedButtons.end();
// }

System* Context::getSystem(std::string name) {
	for (auto &system : systems) {
		if (system->name == name) return system;
	}
}

void Context::addSystem(char* name, System* system, bool persistent, bool enabled) {
	system->name = name;
	system->toggle(persistent || enabled);
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
