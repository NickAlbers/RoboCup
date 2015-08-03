#include <Servo.h>
#include <XBOXRECV.h>
#include "Config.h"
#include "circBuf.h"
#include "Robot.h"

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

  //Create the robot "Bagger"!!!
  static _Robot Bagger;
  
  opMode = AUTONOMOUS;
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
      collisionDetect(&Bagger);//Poll collision detection sensors and evade if neccessary
      packageDetect(&Bagger);
      
      autonomousDrive(&Bagger);
      break;
  }
  
  //----------------
  //TESTING:
  //collisionDetect(&Bagger);
  //updateSensors(&Bagger);
  //readIRMed(IRmed_L_Pin);
  //----------------
  
  
  loopCount ++;
  delay(10); //This makes stuff work
}
