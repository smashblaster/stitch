#include <Nintendo.h>
#include <string>
#include <vector>

#pragma once

class System;

class Context {
	private:
		const int stepIntervalConsole = 1;
		const int stepIntervalDolphin = 7;
		const int maxDashBufferConsole = 2;
		const int maxDashBufferDolphin = 8;

	public:
		CGamecubeConsole console;
		CGamecubeController controller;
		Gamecube_Data_t data = defaultGamecubeData;
		bool enabled = true;
		bool init = false;
		bool isDolphin = false;
		bool meta = false;
		bool rumble = false;
		int maxDashBuffer = maxDashBufferConsole;
		int stepInterval = stepIntervalConsole;
		std::vector<System*> systems;
		std::vector<std::string> pressedButtons;
		std::vector<std::string> releasedButtons;
		unsigned long debug;

		Context(int consolePin, int controllerPin): console(consolePin), controller(controllerPin) {}
		~Context() {}

		uint8_t get(std::string button) { get(button, data.report); }
		uint8_t get(std::string button, Gamecube_Report_t state);
		void set(std::string button, uint8_t value);

		void press(std::string button) { set(button, 1); }
		void release(std::string button) { set(button, 0); }
		bool pressed(std::string button);
		bool released(std::string button);
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
		}
};
