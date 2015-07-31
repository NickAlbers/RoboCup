#include <Servo.h>
#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#define HANDBRAKE 0
#define AUTONOMOUS 2
#define GETPACKAGE 3
#define AVOIDOBSTACLE 4
#define TURNING 0
#define DRIVING 1
#define SAFEDISTANCE 25 //Value in centimeters

int opMode = HANDBRAKE;
const int IRright_Pin = A0;
const int IRleft_Pin = A1;

//OperationType operationMode = REMOTECONTROL;
int  operationMode = REMOTECONTROL;
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
  setupIRMed();
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
//  readIRMed();
  loopCount ++;
  delay(10); //This makes stuff work
}
