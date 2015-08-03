#include <Servo.h>
#include <XBOXRECV.h>
#include "Config.h"
#include "circBuf.h"

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
  Init_Circ_Buff (&irMedLeftBuff, BUFF_SIZE);
  Init_Circ_Buff (&irMedRightBuff, BUFF_SIZE);
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
      updateSensors();
      autonomousDrive();
      collisionDetect();//Poll collision detection sensors and evade if neccessary
      packageDetect();
      break;
  }
  loopCount ++;
  delay(100); //This makes stuff work
}
