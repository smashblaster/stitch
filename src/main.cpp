#include "Arduino.h"
#include "wavesine.cc"

// Pin definitions
#define pinLed LED_BUILTIN

WaveSine wavesine(3, 4);

void setup() {
	Serial.begin(9600);
	pinMode(pinLed, OUTPUT);
}

void loop() {
	wavesine.update();
}
