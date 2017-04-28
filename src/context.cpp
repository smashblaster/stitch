#include <Nintendo.h>
#include <string>
#include <vector>

#ifndef CONTEXT
#define CONTEXT

class Context {
	public:
		CGamecubeConsole console;
		CGamecubeController controller;
		Gamecube_Data_t data;
		Gamecube_Report_t prevState;
		Gamecube_Report_t state;
		bool debug = false;
		bool enabled = true;
		bool init = false;
		bool meta = false;
		bool rumble = false;
		std::vector<std::string> pressedButtons;
		std::vector<std::string> releasedButtons;

		Context(int consolePin, int controllerPin): console(consolePin), controller(controllerPin) {}

		~Context() {}

		uint8_t get(std::string button) { get(button, state); }

		uint8_t get(std::string button, Gamecube_Report_t state) {
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

		void set(std::string button, uint8_t value) {
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

		void press(std::string button) { set(button, 1); }
		void release(std::string button) { set(button, 0); }

		bool pressed(std::string button) {
			return std::find(pressedButtons.begin(), pressedButtons.end(), button) != pressedButtons.end();
		}

		bool released(std::string button) {
			return std::find(releasedButtons.begin(), releasedButtons.end(), button) != releasedButtons.end();
		}

		bool down(std::string button) { return get(button, data.report) == 1; }
};

#endif
