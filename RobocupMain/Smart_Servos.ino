#include "Herkulex.h"

/*
0xfd or 253 is the default
0xfe or 254 is broadcast, ie all motors
*/

void setupSmartServos()
{
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board

  Herkulex.beginSerial2(115200); //open serial port 2 to talk to the motors
  Herkulex.reboot(1);            //reboot motor
  Herkulex.reboot(2);            //reboot motor

  delay(500);
  Herkulex.initialize();         //initialize motors

  //Assert the servos to the forwards position and set the LEDS to red to indicate ready
  Herkulex.moveOne(1, 512, 1000, LED_RED);
  Herkulex.moveOne(2, 512, 1000, LED_RED);
  sweepState = SWEEPIN;

}

void toggleJaws(int servo1, int servo2)
{
  static long nextSweep = 0;

  if ((millis() <= nextSweep)) {
    return;
  }

  switch (sweepState) {
    case SWEEPIN: //Green LED indicates in
      Herkulex.moveOne(servo1, 812, SWEEPTIME, LED_GREEN); // A change of 300 indicates a 90 degree angle
      Herkulex.moveOne(servo2, 212, SWEEPTIME, LED_GREEN);
      Serial.println("Sweeping In");
      sweepState = SWEEPOUT;
      break;
    case SWEEPOUT: //Blue LED indicates in
      Herkulex.moveOne(servo1, 512, SWEEPTIME, LED_BLUE);
      Herkulex.moveOne(servo2, 512, SWEEPTIME, LED_BLUE);
      Serial.println("Sweeping Out");
      sweepState = SWEEPIN;
      break;
  }

  nextSweep = millis() + SWEEPTIME;
}

void closeJaws(int servo1, int servo2)
{
  UpdateLED(0,0,255); //Flash LED strips blue to simulate jaws closing
  Herkulex.moveOne(servo1, 812, SWEEPTIME, LED_GREEN); // A change of 300 indicates a 90 degree angle
  Herkulex.moveOne(servo2, 212, SWEEPTIME, LED_GREEN);
  Serial.println("Sweeping In");
}

void openJaws(int servo1, int servo2)
{
  UpdateLED(0,255,0); //Flash LED strips green to simulate jaws opening
  Herkulex.moveOne(servo1, 512, SWEEPTIME, LED_BLUE);
  Herkulex.moveOne(servo2, 512, SWEEPTIME, LED_BLUE);
  Serial.println("Sweeping In");
}

