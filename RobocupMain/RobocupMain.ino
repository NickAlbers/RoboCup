#include <Servo.h>
#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#define READYSTATE 0
#define REMOTECONTROL 1
#define AUTONOMOUS 2

int operationMode = REMOTECONTROL;
int xboxConnected = false; //Assume no xbox controller is connected
int loopCount = 0;

//Declare globals
Servo leftServo;      // create servo object to control a servo
Servo rightServo;      // create servo object to control a servo
USB Usb;
XBOXRECV Xbox(&Usb);

//***********************************************************************************************
//Setup Code goes here
//***********************************************************************************************
void setup()
{
  setupIR();
  setupDCMotors();
  setupXboxReceiver();
}

//***********************************************************************************************
//The main program loop
//***********************************************************************************************
void loop()
{
  Usb.Task();
  modeSelect();

  //If remote control enabled give user control via the Xbox controller.
  //otherwise enable autonomous control
  if (operationMode == REMOTECONTROL) {
    xboxControl();
  }
  else if (operationMode == AUTONOMOUS) {
    autonomousControl();
  }
  
  //Every tenth loop of main execute this (Time slice scheduler)
//  if ((loopCount % 10) == 0)
//  {
//    readIR();
//  }
//  delay(10); //This makes stuff work
  loopCount ++;
}
