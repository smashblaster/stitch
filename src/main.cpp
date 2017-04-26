#include "Arduino.h"
#include "wavesine.cpp"

#define pinLed LED_BUILTIN

WaveSine wavesine(3, 4);
const int baud = 9600;

void setup() {
	Serial.begin(baud);
	pinMode(pinLed, OUTPUT);

	char json[] = "{"
		"\"backdash\": \"true\","
		"\"remap\": \"true\","
		"\"rumble\": \"true\""
	"}";
	wavesine.setup(json);
}

void loop() {
	wavesine.update();
}
