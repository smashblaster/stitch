#include "Arduino.h"
#include "stitch.cpp"

#define pinLed LED_BUILTIN

Stitch* stitch;
const int baud = 9600;
const int consolePin = 3;
const int controllerPin = 4;

void setup() {
	Serial.begin(baud);
	pinMode(pinLed, OUTPUT);

	char json[] = "{"
		"\"angles\": \"true\","
		"\"backdash\": \"true\","
		"\"debug\": \"false\","
		"\"remap\": \"false\","
		"\"rumble\": \"false\""
	"}";
	stitch = new Stitch(consolePin, controllerPin, json);
}

void loop() {
	stitch->update();
}
