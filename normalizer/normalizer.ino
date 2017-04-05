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

void init(auto report, Gamecube_Data_t *data) {
	// Zero the controller out on startup
	(*data).origin = controller.getOrigin();

	// Reset x-axis
	center = report.xAxis;
}

void map(auto report, Gamecube_Data_t *data) {
	// Reporting all buttons, sticks, sliders
	(*data).report.a = report.a;
	(*data).report.b = report.b;
	(*data).report.x = report.x;
	(*data).report.y = report.y;
	(*data).report.start = report.start;

	(*data).report.dleft = report.dleft;
	(*data).report.dright = report.dright;
	(*data).report.ddown = report.ddown;
	(*data).report.dup = report.dup;

	(*data).report.z = report.z;
	(*data).report.r = report.r;
	(*data).report.l = report.l;

	(*data).report.xAxis = report.xAxis;
	(*data).report.yAxis = report.yAxis;
	(*data).report.cxAxis = report.cxAxis;
	(*data).report.cyAxis = report.cyAxis;
	(*data).report.left = report.left;
	(*data).report.right = report.right;
}

void dashback(auto report, Gamecube_Data_t *data) {
	// If the x axis is between these two than set buffer to eight
	if (report.xAxis > center - deadZone - 1 && report.xAxis < center + deadZone - 1) {
		dashBuffer = maxDashBuffer;
	}

	if (report.xAxis < center - deadZone || report.xAxis > center + deadZone) {
		// Automatically dashes and skips all buffer if you enter running state
		if (report.xAxis > center + smashZone || report.xAxis < center - smashZone) {
			(*data).report.xAxis = report.xAxis;
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
	auto report = controller.getReport();
	Gamecube_Data_t data = defaultGamecubeData;

	if (isInit == false) {
		init(report, &data);
		isInit = true;
	}

	map(report, &data);

	dashback(report, &data);

	// Sends the data to the console
	if (!console.write(data)) {
		delay(100);
		console.write(data);
	}

	controller.setRumble(data.status.rumble);
}
