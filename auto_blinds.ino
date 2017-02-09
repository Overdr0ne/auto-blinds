/*
	 Stepper Motor Control - one revolution

	 This program drives a unipolar or bipolar stepper motor.
	 The motor is attached to digital pins 8 - 11 of the Arduino.

	 The motor should revolve one revolution in one direction, then
	 one revolution in the other direction.


	 Created 11 Mar. 2007
	 Modified 30 Nov. 2009
	 by Tom Igoe

 */

#include <Stepper.h>
#include <RCSwitch.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
//Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);

RCSwitch mySwitch = RCSwitch();
int nSteps = 2;
int onSig = 11111;
int offSig = 11112;
int value = 0;

void setup() {
	// set the speed at 60 rpm:
	myStepper.setSpeed(10);
	// initialize the serial port:
	Serial.begin(9600);
	mySwitch.enableReceive(0);
}

void loop() {
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);

  //if (mySwitch.available() && (value != mySwitch.getReceivedValue())) {
  if (mySwitch.available()) {
    value = mySwitch.getReceivedValue();
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("data recieved:");
    Serial.println(value);

    if(value == onSig) {
      // step one revolution  in one direction:
      myStepper.step(nSteps*stepsPerRevolution);
      delay(500);
      mySwitch.resetAvailable();
    }
    
    if(value == offSig) {
      // step one revolution  in one direction:
      myStepper.step(-(nSteps*stepsPerRevolution));
      delay(500);
      mySwitch.resetAvailable();
    }
  }
}
