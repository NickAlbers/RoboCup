
//Include 3rd party libraries
#include <Herkulex.h>
#include <Servo.h>
#include <XBOXRECV.h>
#include <NewPing.h>

//Include standard C modules
#include <stdio.h>

//Include user created modules
//#include <SoftwareSerial.h>
#include "PololuLedStrip.h"
#include "Herkulex.h"
#include "Herkulex.h"
#include "circBuf.h"

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
  
  pinMode(30, OUTPUT);   //Sneakily out the LED initilisation here
  pinMode(38, INPUT);
  pinMode(39, INPUT);
  pinMode(40, INPUT);
  pinMode(41, INPUT);
  pinMode(49, OUTPUT);   //Pin 49 is used to enable IO power
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
  //setupIMU();
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

  //Select the mode of operation for the main loop
  Usb.Task();
  modeSelect(&Bagger);

  //If remote control enabled give user control via the Xbox controller.
  //Operation mode decision tree
  switch (opMode) {
    case HANDBRAKE:
      driveStop();
      turnOffLED();
      break;
    case REMOTECONTROL:
      turnOnLED();
      xboxControl(&Bagger);
//      if (millis() > nextIMUread) {
//      readIMU(&Bagger);
//      nextIMUread = millis() + 1000;
//      }
      break;
    case AUTONOMOUS:
//    Serial.println("TO SCHEDULER");
      Task_Scheduler(&Bagger);
//    Serial.println("BACK FROM SCHEDULER");
//      updateSensors(&Bagger);
//      readIMU(&Bagger);
//      collisionDetect(&Bagger);//Poll collision detection sensors and evade if neccessary
//      packageDetect(&Bagger);
//      if (collectFlag == true) //Tell the robot to collect the weight
//      {
//        openJaws(1, 2); // Open Jaws ready for next package
//        while (packageCollect(&Bagger) == false)
//        {
//          //Do stuff
//        }
//      }
//      autonomousDrive(&Bagger);
      break;
  }
  
//  else if (packageDetect() == true)
//  {
//    //Execute Collection Code
//    packageCollect()
//    packageCount++;
  
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

  
  loopCount ++;

//  delay(10); //This makes stuff work
}
