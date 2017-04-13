#include "Arduino.h"
#include "Nintendo.h"

#include "map.cpp"
#include "debug.cpp"
#include "remap.cpp"
#include "dashback.cpp"

CGamecubeController controller(4);
CGamecubeConsole console(3);

// Pin definitions
#define pinLed LED_BUILTIN

bool isInit = false;
bool isPassthrough = false;

Map mapper;
Debug debugger;
Remap remapper;
Dashback dasher;

void setup() {
	Serial.begin(9600);
	pinMode(pinLed, OUTPUT);
}

void init(Gamecube_Report_t state, Gamecube_Data_t *data) {
	// TODO: move to map module
	// Zero the controller out on startup
	(*data).origin = controller.getOrigin();

	mapper.init(state, data);
	debugger.init(state, data);
	remapper.init(state, data);
	dasher.init(state, data);
}

void loop() {
	// Just stops the code if no controller is found
	if (!controller.read()) {
		isInit = false;
		delay(100);
		return;
	}

	// Gets the data of controller
	Gamecube_Report_t state = controller.getReport();
	Gamecube_Data_t data = defaultGamecubeData;

	if (isInit == false) {
		init(state, &data);
		isInit = true;
	}

	mapper.update(state, &data);

	// Map dleft => toggle noop
	if (state.dleft == 1) {
		data.report.dleft = 0;
		isPassthrough = (isPassthrough == true) ? false : true;
		data.report.start = 1;
	}

	if (isPassthrough == false) {
		// debugger.update(state, &data);
		remapper.update(state, &data);
		dasher.update(state, &data);
	}

	// Sends the data to the console
	if (!console.write(data)) {
		delay(100);
		console.write(data);
	}

	controller.setRumble(data.status.rumble);
}
