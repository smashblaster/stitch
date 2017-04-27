#include "Arduino.h"
#include "wavesine.cpp"

#define pinLed LED_BUILTIN

WaveSine* wavesine;
const int baud = 9600;
const int consolePin = 3;
const int controllerPin = 4;

void setup() {
	Serial.begin(baud);
	pinMode(pinLed, OUTPUT);

	char json[] = "{"
		"\"backdash\": \"true\","
		"\"remap\": \"true\","
		"\"rumble\": \"true\""
	"}";
	wavesine = new WaveSine(consolePin, controllerPin, json);
}

void loop() {
	wavesine->update();
}
