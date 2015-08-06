
#include <Adafruit_TCS34725.h>

#include "Herkulex.h"
//#include <SoftwareSerial.h>

#include <Servo.h>
#include <XBOXRECV.h>
#include "Config.h"
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
  setupSmartServos();
  setupColourSensor();
  

}

//***********************************************************************************************
//The main program loop
//***********************************************************************************************
void loop()
{
  sweepServos(1, 2);
  Usb.Task();
  modeSelect();
  

  //Create the robot "Bagger"!!!
  static _Robot Bagger;
//  static int servoSpin = 1000;
  static long nextServoTest = millis();

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
      break;
  }
  
  readColourSensor();
  //----------------
  //TESTING:
  //collisionDetect(&Bagger);
  //updateSensors(&Bagger);
  //readIRMed(IRmed_L_Pin);
  //----------------

//    if (servoSpin == 1000) {
//      servoSpin = 1900;
//      leftTrayServo.writeMicroseconds(servoSpin);
//    }
//    else if (servoSpin == 1900) {
//      servoSpin = 1000;
//      leftTrayServo.writeMicroseconds(servoSpin);
//    }
//    nextServoTest = millis() + 1500;
//    Serial.println(servoSpin);

  loopCount ++;
  delay(10); //This makes stuff work
}
