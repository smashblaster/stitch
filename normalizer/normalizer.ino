#include "Nintendo.h"

CGamecubeController controller(4);
CGamecubeConsole console(3);

// Pin definitions
#define pinLed LED_BUILTIN

// Zero the buffer and control stick
int bufferrr = 0;
int i = 1;
int X = 128;

void setup() {
	Serial.begin(9600);
	// Set up debug led
	pinMode(pinLed, OUTPUT);
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

	// Zeros the x-Axis in the code
	if (i == 1){
		int X = r1.xAxis;
		i = 0;
	}

	// If the x axis is between these two than set buffer to eight
	if (r1.xAxis > X - 21 && r1.xAxis < X + 21){
		// CHANGE THIS TO 8 IF PLAYING ON DOLPHIN
		bufferrr = 2;
	}

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

	// The dashback modification
	if (r1.xAxis < X - 22 || r1.xAxis > X + 22){
		// Automatically dashes and skips all buffer if you enter running state
		if (r1.xAxis > X + 97 || r1.xAxis < X - 97){
			data.report.xAxis = r1.xAxis;
			bufferrr = 0;
		}
		if (bufferrr > 0){
			// Set x-axis to neutral
			data.report.xAxis = 128;
			bufferrr = bufferrr - 1;
		}
	}

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
