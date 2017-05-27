#include "context.hpp"
#include "systems/system.hpp"

uint8_t Context::get(Inputs button, Gamecube_Report_t state) {
	if (button == Inputs::A) return state.a;
	if (button == Inputs::B) return state.b;
	if (button == Inputs::X) return state.x;
	if (button == Inputs::Y) return state.y;
	if (button == Inputs::L) return state.l;
	if (button == Inputs::R) return state.r;
	if (button == Inputs::Z) return state.z;
	if (button == Inputs::START) return state.start;
	if (button == Inputs::DDOWN) return state.ddown;
	if (button == Inputs::DLEFT) return state.dleft;
	if (button == Inputs::DRIGHT) return state.dright;
	if (button == Inputs::DUP) return state.dup;
	if (button == Inputs::CXAXIS) return state.cxAxis;
	if (button == Inputs::CYAXIS) return state.cyAxis;
	if (button == Inputs::LEFT) return state.left;
	if (button == Inputs::RIGHT) return state.right;
	if (button == Inputs::XAXIS) return state.xAxis;
	if (button == Inputs::YAXIS) return state.yAxis;
	return 0;
}

void Context::set(Inputs button, uint8_t value) {
	if (button == Inputs::A) data.report.a = value;
	if (button == Inputs::B) data.report.b = value;
	if (button == Inputs::X) data.report.x = value;
	if (button == Inputs::Y) data.report.y = value;
	if (button == Inputs::L) data.report.l = value;
	if (button == Inputs::R) data.report.r = value;
	if (button == Inputs::Z) data.report.z = value;
	if (button == Inputs::START) data.report.start = value;
	if (button == Inputs::DDOWN) data.report.ddown = value;
	if (button == Inputs::DLEFT) data.report.dleft = value;
	if (button == Inputs::DRIGHT) data.report.dright = value;
	if (button == Inputs::DUP) data.report.dup = value;
	if (button == Inputs::CXAXIS) data.report.cxAxis = value;
	if (button == Inputs::CYAXIS) data.report.cyAxis = value;
	if (button == Inputs::LEFT) data.report.left = value;
	if (button == Inputs::RIGHT) data.report.right = value;
	if (button == Inputs::XAXIS) data.report.xAxis = value;
	if (button == Inputs::YAXIS) data.report.yAxis = value;
}

bool Context::pressed(Inputs button) {
	return std::find(pressedButtons.begin(), pressedButtons.end(), button) != pressedButtons.end();
}

// bool Context::released(Inputs button) {
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
