#include <Nintendo.h>
#include <string>
#include <vector>

#pragma once

class System;

class Context {
	private:
		const int dolphinMultiplier = 7;
		const int maxDashBufferConsole = 2;
		const int maxDashBufferDolphin = maxDashBufferConsole * dolphinMultiplier;
		const int stepIntervalConsole = 1;
		const int stepIntervalDolphin = stepIntervalConsole * dolphinMultiplier;

	public:
		CGamecubeConsole console;
		CGamecubeController controller;
		Gamecube_Data_t data = defaultGamecubeData;
		bool enabled = true;
		bool init = false;
		bool isDolphin = false;
		bool rumble = false;
		const int gridOffset = 129;
		int maxDashBuffer = maxDashBufferConsole;
		int stepInterval = stepIntervalConsole;
		std::vector<System*> systems;
		unsigned long debug = 0;

		Context(int consolePin, int controllerPin): console(consolePin), controller(controllerPin) {}
		~Context() = default;

		uint8_t get(std::string button) { get(button, data.report); }
		uint8_t get(std::string button, Gamecube_Report_t state);
		void set(std::string button, uint8_t value);

		void press(std::string button) { set(button, 1); }
		void release(std::string button) { set(button, 0); }
		bool down(std::string button) { return get(button, data.report) > 0; }

		void setState(Gamecube_Report_t state) { data.report = state; }

		System* getSystem(std::string name);
		void addSystem(char* name, System* system, bool persistent = false, bool enabled = false);
		void enableSystem(std::string name) { toggleSystem(name, true); }
		void disableSystem(std::string name) { toggleSystem(name, false); }
		void toggleSystem(std::string name);
		void toggleSystem(std::string name, bool value);
		void toggleSystem(System* system);
		void toggleSystem(System* system, bool value);

		// Profiler
		void begin() { debug = micros(); }
		void end() { debug = micros() - debug; }

		void dolphin(bool enabled) {
			isDolphin = enabled;
			stepInterval = (enabled) ? stepIntervalDolphin : stepIntervalConsole;
			maxDashBuffer = (enabled) ? maxDashBufferDolphin : maxDashBufferConsole;
			init = false;
		}

		void setOrigin(int x = 128, int y = 128) {
			// Zero out the controller
			data.origin = controller.getOrigin();
			data.report = controller.getReport();

			// Set a consistent origin.
			data.origin.inititalData.xAxis = x;
			data.origin.inititalData.yAxis = y;
		}
};
