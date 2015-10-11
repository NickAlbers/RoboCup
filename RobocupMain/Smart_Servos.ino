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
  Jaws_Open(1, 2);
  Tray_Lower(42);
  sweepState = SWEEPIN;
}

//***********************************************************************************************
// Jaw Functions
//***********************************************************************************************

void Jaws_Toggle(int servo1, int servo2)
{
  Serial.println("Toggling Smart Servos");
  static long nextSweep = 0;

  if ((millis() <= nextSweep)) {
    return;
  }

  switch (sweepState) {
    case SWEEPIN: //Green LED indicates in
      Herkulex.moveOne(servo1, 812, SWEEPTIME, LED_GREEN); // A change of 300 indicates a 90 degree angle
      Herkulex.moveOne(servo2, 212, SWEEPTIME, LED_GREEN);
      sweepState = SWEEPOUT;
      break;
    case SWEEPOUT: //Blue LED indicates in
      Herkulex.moveOne(servo1, 512, SWEEPTIME, LED_BLUE);
      Herkulex.moveOne(servo2, 512, SWEEPTIME, LED_BLUE);
      sweepState = SWEEPIN;
      break;
  }

  nextSweep = millis() + SWEEPTIME;
}

void Jaws_Close(int servo1, int servo2)
{ 
  Serial.println("Closing jaws");
  
  //Set the time of the weight collection
  Jaws_OpenTime = millis() + JAWSCLOSEPERIOD;
  
  LED_Update(0,0,255); //Flash LED strips blue to simulate jaws closing
  Herkulex.moveOne(servo1, 812, SWEEPTIME, LED_GREEN); // A change of 300 indicates a 90 degree angle
  Herkulex.moveOne(servo2, 212, SWEEPTIME, LED_GREEN);
}

void Jaws_Open(int servo1, int servo2)
{
  LED_Update(0,255,0); //Flash LED strips green to simulate jaws opening
  Herkulex.moveOne(servo1, 512, SWEEPTIME, LED_BLUE);
  Herkulex.moveOne(servo2, 512, SWEEPTIME, LED_BLUE);
}

//***********************************************************************************************
// Tray Functions
//***********************************************************************************************

void Tray_Lift(int servo)
{
  trayPosition = TRAYUP;
//  LED_Update(0,255,0); //Flash LED strips green to simulate jaws opening
  Herkulex.moveOneAngle(servo, TRAYUPANGLE, SWEEPTIME, LED_BLUE);
  Serial.println("Lifting Tray");
}

void Tray_Lower(int servo)
{
  trayPosition = TRAYDOWN;
//  LED_Update(0,255,0); //Flash LED strips green to simulate jaws opening
  Herkulex.moveOneAngle(servo, TRAYDOWNANGLE, SWEEPTIME, LED_GREEN);
  Serial.println("Lowering Tray");
  
}
