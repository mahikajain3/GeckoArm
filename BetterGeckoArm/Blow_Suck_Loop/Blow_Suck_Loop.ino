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
int totalTime = 3000;     // Blow/Suck for 3 sec
int maxLoop = 100;        // Number of iterative loops
int holdTime = 2000;      // Hold same pressure for 2 sec

int timePerLoop = totalTime/maxLoop;
int holdTimePerLoop = holdTime/maxLoop;


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

  // Loop 100 times, total time: 3000 ms
  for(int i=0; i<=maxLoop; i++){
  
    // Blow air
    switchOnPump(2, 100);
    blow();

    // Read pressure
    pressure = readPressure();
    Serial.println(pressure);

    //  Wait for some time (Time per loop)
    delay(timePerLoop); 

  }

  // Hold postion for 2 sec
  for(int j=0; j<=maxLoop; j++){
  
    // Turn off everything and hold poition
    switchOffPumps();
    closeAllValves();

    // Read pressure
    pressure = readPressure();
    Serial.println(pressure);

    //  Wait for some time (Hold Time per loop)
    delay(holdTimePerLoop); 

  }

  // Loop 100 times, total time: 3000 ms
  for(int i=0; i<=maxLoop; i++){
  
    // Suck air
    switchOnPump(1, 100);
    suck();

    // Read pressure
    pressure = readPressure();
    Serial.println(pressure);

    //  Wait for some time (Time per loop)
    delay(timePerLoop); 

  }

  // Hold postion for 2 sec
  for(int j=0; j<=maxLoop; j++){
  
    // Turn off everything and hold poition
    switchOffPumps();
    closeAllValves();

    // Read pressure
    pressure = readPressure();
    Serial.println(pressure);

    //  Wait for some time (Hold Time per loop)
    delay(holdTimePerLoop); 

  }
  
  
}
