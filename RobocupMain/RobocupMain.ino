#include <Servo.h>
#include <XBOXRECV.h>
#include "Config.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif
//***********************************************************************************************
//Setup Code goes here
//***********************************************************************************************
void setup()
{
  initVcc();
  setupXboxReceiver();
  setupDCMotors();
  setupIRMed();
  setup_Ultra();
}

//***********************************************************************************************
//The main program loop
//***********************************************************************************************
void loop()
{
  Usb.Task();
  modeSelect();

  //If remote control enabled give user control via the Xbox controller.
  //Operation mode decision tree
  switch (opMode) {
    case HANDBRAKE:
      driveStop();
      break;
    case REMOTECONTROL:
      xboxControl();
      break;
    case AUTONOMOUS:
      autonomousDrive();
      collisionDetect();//Poll collision detection sensors and evade if neccessary
      packageDetect();
      break;
  }
  loopCount ++;
  delay(10); //This makes stuff work
}
