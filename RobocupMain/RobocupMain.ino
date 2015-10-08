#include <Herkulex.h>
#include <Servo.h>
#include <XBOXRECV.h>
#include <stdio.h>
//#include <SoftwareSerial.h>
#include "PololuLedStrip.h"
#include "Herkulex.h"
//#include "Scheduler.h"

//Declare this last as the configuration file depends on the other includes
#include "Config.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

//***********************************************************************************************
//Setup Code goes here
//***********************************************************************************************

void initVcc()
{
  // turn Vcc on (5V)
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);
}

void setup()
{
  initVcc();
  setupXboxReceiver();
  setupDCMotors();
  setupIR();
  setupUltra();
  setupSmartServos();
  setupIMU();
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
      readIMU();
      readMagnetometer();
      break;
    case AUTONOMOUS:
      updateSensors(&Bagger);
      readIMU();
      readMagnetometer();
      collisionDetect(&Bagger);//Poll collision detection sensors and evade if neccessary
      packageDetect(&Bagger);
      packageCollect(&Bagger);
      if (collectFlag == true) //Tell the robot to collect the weight
      {
        openJaws(1, 2); // Open Jaws ready for next package
        while (packageCollect(&Bagger) == false)
        {
          //Do stuff
        }
      }
      autonomousDrive(&Bagger);
//    packageCount++;
  }
//  
//  if (packageCount == 3)
//  {
//    while (onBase != true)
//    {
//    homeSeek();
//    if (collisionDetect() == true)
//    {
//      //Execute Avoidance Code
//    }
//  }  
//  else if (onBase == true)
//  {
//    //UnloadPackages
//    packageCount = 0;
//  }
//  else if (onBase == true)
//  {
//    //UnloadPackages
//    packageCount = 0;
//  }
//      break;
//  }

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
  delay(10); //This makes stuff work
}
