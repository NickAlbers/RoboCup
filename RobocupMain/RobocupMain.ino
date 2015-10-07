#include <Herkulex.h>
//#include <SoftwareSerial.h>
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
  //Create the robot "Bagger"!!!
  static _Robot Bagger;
  
  Usb.Task();
  modeSelect(&Bagger);

  //If remote control enabled give user control via the Xbox controller.
  //Operation mode decision tree
  switch (opMode) {
    case HANDBRAKE:
      driveStop();
      break;
    case REMOTECONTROL:
      xboxControl();
      if (millis() > nextIMUread) {
      readIMU(&Bagger);
      nextIMUread = millis() + 1000;
      }
      break;
    case AUTONOMOUS:
      Task_Scheduler(&Bagger);
//      updateSensors(&Bagger);
//      readIMU(&Bagger);
//      collisionDetect(&Bagger);//Poll collision detection sensors and evade if neccessary
//      packageDetect(&Bagger);
      if (collectFlag == true) //Tell the robot to collect the weight
      {
        openJaws(1, 2); // Open Jaws ready for next package
        while (packageCollect(&Bagger) == false)
        {
          //Do stuff
        }
      }
      autonomousDrive(&Bagger);
      break;
  }
  
//  else if (packageDetect() == true)
//  {
//    //Execute Collection Code
//    packageCollect()
//    packageCount++;
//  }
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

  //----------------
  //TESTING:
  //collisionDetect(&Bagger);
  //updateSensors(&Bagger);
  //readIRMed(IRmed_L_Pin);
  //----------------
  loopCount ++;
  delay(10); //This makes stuff work
}
