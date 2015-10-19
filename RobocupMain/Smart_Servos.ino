#include "Herkulex.h"

/*
0xfd or 253 is the default
0xfe or 254 is broadcast, ie all motors
*/

void setupSmartServos()
{
 Serial.println("SetUp Smart Servos");

  Herkulex.beginSerial2(115200); //open serial port 2 to talk to the motors
  Herkulex.reboot(1);            //reboot motor
  Herkulex.reboot(2);            //reboot motor
  Herkulex.reboot(42);            //reboot motor

  delay(500);
  Herkulex.initialize();         //initialize motors

  //Assert the servos to the forwards or downwards position and set the LEDS to red to indicate ready
  //  Herkulex.moveOne(1, 512, 1000, LED_RED);
  //  Herkulex.moveOne(2, 512, 1000, LED_RED);
  openJaws(1, 2);
  lowerTray(42);
  sweepState = SWEEPIN;
}

void toggleJaws(int servo_right, int servo_left)
{
  Serial.println("Toggling Smart Servos");
  static long nextSweep = 0;

  if ((millis() <= nextSweep)) {
    return;
  }

  switch (sweepState) {
    case SWEEPIN: //Green LED indicates in
      Herkulex.moveOne(servo_right, 842, SWEEPTIME, LED_GREEN); // A change of 300 indicates a 90 degree angle
      Herkulex.moveOne(servo_left, 192, SWEEPTIME, LED_GREEN);
      Serial.println("Sweeping In");
      sweepState = SWEEPOUT;
      break;
    case SWEEPOUT: //Blue LED indicates in
      Herkulex.moveOne(servo_right, 562, SWEEPTIME, LED_BLUE);
      Herkulex.moveOne(servo_left, 512, SWEEPTIME, LED_BLUE);
      Serial.println("Sweeping Out");
      sweepState = SWEEPIN;
      break;
  }

  nextSweep = millis() + SWEEPTIME;
}

void closeJaws(int servo_right, int servo_left)
{ 
  Serial.println("Closing jaws");
  
  //Set the time of the weight collection
  Jaws_OpenTime = millis() + JAWSCLOSEPERIOD;
//  UpdateLED(0,0,255); //Flash LED strips blue to simulate jaws closing
  Herkulex.moveOne(servo_right, 862, SWEEPTIME, LED_GREEN); // A change of 300 indicates a 90 degree angle
  Herkulex.moveOne(servo_left, 212, SWEEPTIME, LED_GREEN);
  Serial.println("Sweeping In");
  
  
}

void openJaws(int servo_right, int servo_left)
{
//  UpdateLED(0,255,0); //Flash LED strips green to simulate jaws opening
  Herkulex.moveOne(servo_right, 512, SWEEPTIME, LED_BLUE);
  Herkulex.moveOne(servo_left, 512, SWEEPTIME, LED_BLUE);
  Serial.println("Sweeping In");
}

void liftTray(int servo)
{
  trayPosition = TRAYUP;
//  UpdateLED(0,255,0); //Flash LED strips green to simulate jaws opening
  Herkulex.moveOneAngle(servo, TRAYUPANGLE, SWEEPTIME, LED_BLUE);
  Serial.println("Lifting Tray");
}

void lowerTray(int servo)
{
  trayPosition = TRAYDOWN;
//  UpdateLED(0,255,0); //Flash LED strips green to simulate jaws opening
  Herkulex.moveOneAngle(servo, TRAYDOWNANGLE, SWEEPTIME, LED_GREEN);
  Serial.println("Lowering Tray");
  
}
