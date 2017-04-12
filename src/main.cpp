#include "Arduino.h"
#include "Nintendo.h"

CGamecubeController controller(4);
CGamecubeConsole console(3);

// Pin definitions
#define pinLed LED_BUILTIN

bool isInit = false;
bool isPassthrough = false;

void setup() {
	Serial.begin(9600);
	pinMode(pinLed, OUTPUT);
}

void init(Gamecube_Report_t state, Gamecube_Data_t *data) {
	// TODO: move to map module
	// Zero the controller out on startup
	(*data).origin = controller.getOrigin();
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

	map(state, &data);

	// Map dleft => toggle noop
	if (state.dleft == 1) {
		data.report.dleft = 0;
		isPassthrough = (isPassthrough == true) ? false : true;
		data.report.start = 1;
	}

	if (isPassthrough == false) {
		// debug(state, &data);
		// remap(state, &data);
		dashback(state, &data);
	}

	// Sends the data to the console
	if (!console.write(data)) {
		delay(100);
		console.write(data);
	}

	controller.setRumble(data.status.rumble);
}
