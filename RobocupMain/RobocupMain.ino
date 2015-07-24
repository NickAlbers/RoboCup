/*
Useing port S1 and channels S1 and S2 to drive the two motors on the robot.
The motors must be connected through the Sabertooth driver.
The sabertooth must be in mode Microcontroller pulses, independent linear control mode.
1000us to 2000us control the speed and direction. 1500us is stop.
Any speed outside this range will be ignored.
*/
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
int i = 0;

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
  //Setup the Servos
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board

  leftServo.attach(3);  // attaches the servo pin 3 to the servo object
  rightServo.attach(2);  // attaches the servo pin 2 to the servo object

  //setup the Xbox Receiver
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  
  //Enable Timer interrupts
//  pinMode(ledPin, OUTPUT);
//  
//  // initialize timer1 
//  noInterrupts();           // disable all interrupts
//  TCCR1A = 0;
//  TCCR1B = 0;
//  TCNT1  = 0;
//
//  OCR1A = 31250;            // compare match register 16MHz/256/2Hz
//  TCCR1B |= (1 << WGM12);   // CTC mode
//  TCCR1B |= (1 << CS12);    // 256 prescaler 
//  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
//  interrupts();             // enable all interrupts
  
}

//***********************************************************************************************
//The main program loop
//***********************************************************************************************
void loop()
{
  Usb.Task();
  modeSelect();
  //If remote control enabled give user control via the Xbox controller.
  if (operationMode == REMOTECONTROL) {
    xboxControl();
  }
  //If remote control disabled enable autonomous control
  else if (operationMode == AUTONOMOUS) {
    autonomousControl();
  }
  delay(10);
}
