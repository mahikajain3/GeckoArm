#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, neopixelPin, NEO_GRB + NEO_KHZ800);

#define DEBUG 1

int pressure;
int totalTime = 8000;     // Blow/Suck for 8 sec
int maxLoop = 100;        // Number of iterative loops
int holdTime = 7000;      // Hold same pressure for 7 sec

int timePerLoop = totalTime/maxLoop;
int holdTimePerLoop = holdTime/maxLoop;
int state = UN_KNOWN;

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
  Serial.begin(9600);
}



void loop() {
  Serial.println(PORTB);
  // put your main code here, to run repeatedly:
  //digitalWrite(valve, LOW); //Closes valve
  // Loop 100 times, total time: 3000 ms
  //for(int i=0; i<=maxLoop; i++){
  
    // Blow air if red button pressed
    if (readBtn(RED) && state != BLOWING) {
    // switch on pumps to 50% power
    switchOnPump(2, 100);
    switchOffPump(1);
    blow();
    state = BLOWING;
  }

  
  // Hold postion for 2 sec
  /*for(int j=0; j<=maxLoop; j++){
  
    // Turn off everything and hold poition
    switchOffPumps();
    closeAllValves();

    delay(holdTimePerLoop);*/
  
  
  // Loop 100 times, total time: 3000 ms
  //for(int i=0; i<=maxLoop; i++){
  
    // Suck air if blue button pressed
    else if (readBtn(BLUE) && state != SUCKING) {
    // switch on pumps to 50% power
    switchOnPump(1, 100);
    switchOffPump(2);
    suck();
    state = SUCKING;
  }

  // if nither button is pressed, vent (but blow for a bit to let go of the object)
  else if (!readBtn(BLUE) && !readBtn(RED) && state != VENTING) {
    switchOnPump(1, 100);
    blow();
    delay(holdTimePerLoop);
    switchOffPumps();
    vent();
    state = VENTING;
  }

  delay(holdTimePerLoop);
  
  // Hold postion for 2 sec
  /*for(int j=0; j<=maxLoop; j++){
  
    // Turn off everything and hold poition
    switchOffPumps();
    closeAllValves();
  
    delay(holdTimePerLoop);*/
    
 }
  
