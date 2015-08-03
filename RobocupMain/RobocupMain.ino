#include <Servo.h>
#include <XBOXRECV.h>
#include "CONSTS.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

<<<<<<< HEAD

typedef enum OperationMode { HANDBRAKE, REMOTECONTROL, AUTONOMOUS };
typedef enum RobotState {TURNING, DRIVING, GETPACKAGE, AVOIDOBSTACLE };

=======
#define HANDBRAKE 0
#define REMOTECONTROL 1
#define AUTONOMOUS 2
#define GETPACKAGE 3
#define AVOIDOBSTACLE 4
#define TURNING 0
#define DRIVING 1
>>>>>>> 1fdd9bf3cbd61388bcb2a545a66bfee4d428a79d
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
  readIRLong(IRlong_Pin);
  //readIRMed(IRleft_Pin);
  loopCount ++;
  delay(100); //This makes stuff work
}
