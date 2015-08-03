#include <Servo.h>
#include <XBOXRECV.h>
#include "CONSTS.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif


typedef enum OperationMode { HANDBRAKE, REMOTECONTROL, AUTONOMOUS };
typedef enum RobotState {TURNING, DRIVING, GETPACKAGE, AVOIDOBSTACLE };

#define SAFEDISTANCE 25 //Value in centimeters


OperationMode opMode = HANDBRAKE;
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
      leftServo.write(90);
      rightServo.write(90);
      break;
    case REMOTECONTROL:
      xboxControl();
      break;
    case AUTONOMOUS:
      autonomousControl();
      autonomousDrive();
      break;
  }
//  collisionDetect();
 
 
 //TESTING--------------
  readIRLong(IRlong_L_Pin);
  //readIRMed(IRleft_Pin);
  int cm = readUltra(Ultratrig_L_Pin, Ultraecho_L_Pin);
  Serial.println(cm);
  
 //--------------
 
 
  loopCount ++;
  delay(10); //This makes stuff work
}
