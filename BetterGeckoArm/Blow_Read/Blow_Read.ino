// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// PCB v0.3/v0.4/v0.5

#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, neopixelPin, NEO_GRB + NEO_KHZ800);

#define DEBUG 1

int pressure;

void setup() {
  initializePins();
  pressure = readPressure();

  //neopixels
  pixels.begin();
  for (int i = 0; i < 3; i++) {
    // pixels.Color(red, green, blue)
    pixels.setPixelColor(i, pixels.Color(0, 100, 100));
  }
  pixels.show();
}



void loop() {

  switchOnPump(1, 100);
  
    // Valves
    suck();
  
    pressure = readPressure();
    Serial.println(pressure);

  
  
}
