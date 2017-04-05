#include "Nintendo.h"

CGamecubeController controller(4);
CGamecubeConsole console(3);

// Pin definitions
#define pinLed LED_BUILTIN

int maxDashBuffer = 2;
// int maxDashBuffer = 8;

// Zero the buffer and control stick
int dashBuffer = 0;
int center = 128;
int deadZone = 22;
// int smashZone = 97;
int smashZone = 64;
bool isInit = false;

void setup() {
	Serial.begin(9600);
	pinMode(pinLed, OUTPUT);
}

void init(Gamecube_Report_t state, Gamecube_Data_t *data) {
	// Zero the controller out on startup
	(*data).origin = controller.getOrigin();

	// Reset x-axis
	center = state.xAxis;
}

void map(Gamecube_Report_t state, Gamecube_Data_t *data) {
	// Reporting all buttons, sticks, sliders
	(*data).report.a = state.a;
	(*data).report.b = state.b;
	(*data).report.x = state.x;
	(*data).report.y = state.y;
	(*data).report.start = state.start;

	(*data).report.dleft = state.dleft;
	(*data).report.dright = state.dright;
	(*data).report.ddown = state.ddown;
	(*data).report.dup = state.dup;

	(*data).report.z = state.z;
	(*data).report.r = state.r;
	(*data).report.l = state.l;

	(*data).report.xAxis = state.xAxis;
	(*data).report.yAxis = state.yAxis;
	(*data).report.cxAxis = state.cxAxis;
	(*data).report.cyAxis = state.cyAxis;
	(*data).report.left = state.left;
	(*data).report.right = state.right;
}

void dashback(Gamecube_Report_t state, Gamecube_Data_t *data) {
	// If the x axis is between these two than set buffer to eight
	if (state.xAxis > center - deadZone - 1 && state.xAxis < center + deadZone - 1) {
		dashBuffer = maxDashBuffer;
	}

	if (state.xAxis < center - deadZone || state.xAxis > center + deadZone) {
		// Automatically dashes and skips all buffer if you enter running state
		if (state.xAxis > center + smashZone || state.xAxis < center - smashZone) {
			(*data).report.xAxis = state.xAxis;
			dashBuffer = 0;
		}
		if (dashBuffer > 0) {
			// Set x-axis to neutral
			(*data).report.xAxis = 128;
			dashBuffer = dashBuffer - 1;
		}
	}
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

	dashback(state, &data);

	// Sends the data to the console
	if (!console.write(data)) {
		delay(100);
		console.write(data);
	}

	controller.setRumble(data.status.rumble);
}
