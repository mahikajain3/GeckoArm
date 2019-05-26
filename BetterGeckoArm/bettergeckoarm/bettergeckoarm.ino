//Copyright 2019 Totally Original Code DO NOT STEAL

//Variables to keep track of the position of the joystick.
unsigned int x_pos;
unsigned int y_pos;

//Variable to keep track of whether or not the spring has been activated.
bool spring_state;

//Variables for the servo positions.
short base_pos = 12;
short elbow_pos = 12;
short stabilizer_pos = 12;

//Debug variable so that the print statements can be disabled if need be.
bool _DEBUG = true;

short* ADCdata = 0x78;

//Sets things up
void setup() {
  //If we want to debug, this if statement will be activated, otherwise, it is ignored.
  if(_DEBUG){
    Serial.begin(9600);
  }
  //Setting Port D pins 0-3 as inputs, 4-7 as outputs.
  DDRD = 0xF0;
  //Disconnecting Channel A, setting channel B to Fast PWM, clear on match.
  TCCR0A = 0x23;
  //Setting the clock to divide by 1024 and fixing the rest of the PWM setup.
  TCCR0B = 0x0D;
  TCCR2A = 0x23;
  TCCR2B = 0x0D;
  OCR0A = 250;
  //The initial 24. Changing this will change the servo position.
  OCR0B = 24;
  OCR2A = 250;
  OCR2B = 24;
  //Analog Setup
  ADMUX = 0x40;
  ADCSRA = 0xE6;
  ADCSRB = 0x40;
}

//Runs until the end of time
void loop() {
  ADMUX &= 0;
  base_pos = ((*ADCdata * 26) / 1024) + 12;
  OCR0B = base_pos;

  ADMUX |= 1;
  delay(10);
  elbow_pos = ((*ADCdata * 26) / 1024) + 12;
  OCR2B = elbow_pos;
  stabilizer_pos = elbow_pos;
}
