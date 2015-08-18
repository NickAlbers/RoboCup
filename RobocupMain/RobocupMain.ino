
#include "PololuLedStrip.h"
#include <Servo.h>
#include <XBOXRECV.h>
#include "Config.h"
#include "Herkulex.h"

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
  setupIR();
  setupUltra();
  setupSmartServos();
  //setupColourSensor();
  //setupLED();
}

//***********************************************************************************************
//The main program loop
//***********************************************************************************************
void loop()
{
  Usb.Task();
  modeSelect();
  //Create the robot "Bagger"!!!
  static _Robot Bagger;

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
      updateSensors(&Bagger);
      packageDetect(&Bagger);
      collisionDetect(&Bagger);//Poll collision detection sensors and evade if neccessary
      
      autonomousDrive(&Bagger);
      Serial.println(millis());
      Serial.println(collectionTime);
      if ((millis() > collectionTime) && (millis() > nextSweep)) {
        sweepServos(1, 2);
      }
      break;
  }
  //  LEDGradient();

  //Do this every 25th loop
//  if ((loopCount % 25) == 0) {
//    readColourSensor();
//  }

  //----------------
  //TESTING:
  //collisionDetect(&Bagger);
  //updateSensors(&Bagger);
  //readIRMed(IRmed_L_Pin);
  //----------------
  loopCount ++;
  //delay(10); //This makes stuff work
}
