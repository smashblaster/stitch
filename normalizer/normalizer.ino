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

void dashback(auto report, Gamecube_Data_t *data) {
	if (isInit == false) {
		// Reset x-axis
		center = report.xAxis;
		isInit = true;
	}

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
		delay(100);
		return;
	}

	// Gets the data of controller
	auto r1 = controller.getReport();
	Gamecube_Data_t data = defaultGamecubeData;

	// Zero the controller out on startup
	data.origin = controller.getOrigin();

	// Reporting all buttons, sticks, sliders
	data.report.a = r1.a;
	data.report.b = r1.b;
	data.report.x = r1.x;
	data.report.y = r1.y;
	data.report.start = r1.start;

	data.report.dleft = r1.dleft;
	data.report.dright = r1.dright;
	data.report.ddown = r1.ddown;
	data.report.dup = r1.dup;

	data.report.z = r1.z;
	data.report.r = r1.r;
	data.report.l = r1.l;

	data.report.xAxis = r1.xAxis;
	data.report.yAxis = r1.yAxis;
	data.report.cxAxis = r1.cxAxis;
	data.report.cyAxis = r1.cyAxis;
	data.report.left = r1.left;
	data.report.right = r1.right;

	dashback(r1, &data);

	// Sends the data to the console
	if (!console.write(data)) {
		delay(100);
	}

	if (data.status.rumble) {
		controller.setRumble(true);
	} else {
		controller.setRumble(false);
	}
}
