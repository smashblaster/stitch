#include "Arduino.h"
#include "Nintendo.h"
#include "modules/backdasher.cpp"
#include "modules/debugger.cpp"
#include "modules/mapper.cpp"
#include "modules/remapper.cpp"

CGamecubeController controller(4);
CGamecubeConsole console(3);

// Pin definitions
#define pinLed LED_BUILTIN

bool isInit = false;
bool isPassthrough = false;

Backdasher backdasher;
Debugger debugger;
Mapper mapper;
Remapper remapper;

void setup() {
	Serial.begin(9600);
	pinMode(pinLed, OUTPUT);
}

void init(Gamecube_Report_t state, Gamecube_Data_t *data) {
	mapper.init(state, data, controller);
	debugger.init(state, data, controller);
	remapper.init(state, data, controller);
	backdasher.init(state, data, controller);
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
		backdasher.update(state, &data);
	}

	// Sends the data to the console
	if (!console.write(data)) {
		delay(100);
		console.write(data);
	}

	controller.setRumble(data.status.rumble);
}
