
//Include 3rd party libraries
#include <Herkulex.h>
#include <Servo.h>
#include <XBOXRECV.h>
#include <NewPing.h>
#include <Hx711.h>                      //Include needed library of functions to talk to hx711 IC

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

//***********************************************************************************************
// Initialisation Functions
//***********************************************************************************************

/*Function: initSerial()
 *Initialises the serial readout at BAURDRATE defined in the configuration file.
 */
void initSerial()
{
  // initialize serial communications at set baudrate:
  Serial.begin(BAUDRATE);
}

/*Function: initVcc()
 *Initialises the supply voltage to the relevant pins
 */
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

/*Function: setup()
 *Execute all code needed to run only once, such as setting up any sensors
 */
void setup()
{
  initSerial();
  initVcc();
  setupXboxReceiver();
  setupDCMotors();
  setupIR();
  setupUltra();
  setupSmartServos();
  setupIMU();
//  setupMagenometer()
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
  
  //Detect homebase and set HOMEDIRECTION based on the relevant colour.

  //Select the mode of operation for the main loop
  Usb.Task();
  Xbox_ModeSelect(&Bagger);

  //If remote control enabled give user control via the Xbox controller.
  //Operation mode decision tree
  switch (opMode) {
    case HANDBRAKE:
      Motors_DriveStop();
      LED_TurnOff();
      break;
    case REMOTECONTROL:
      LED_TurnOn();
      xboxControl(&Bagger);
      break;
    case AUTONOMOUS:
      Task_Scheduler(&Bagger);
      break;
  }
  
  loopCount ++;

//  delay(10); //This makes stuff work
}
