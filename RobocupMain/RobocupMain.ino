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

//Declare globals
Servo leftServo;      // create servo object to control a servo
Servo rightServo;      // create servo object to control a servo
int operationMode = true;

#define READYSTATE 0
#define REMOTECONTROL 1
#define AUTONOMOUS 2

USB Usb;
XBOXRECV Xbox(&Usb);

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
}

void loop()
{
  Usb.Task();
  if (Xbox.XboxReceiverConnected && Xbox.Xbox360Connected[0]) {
    modeSelect();
  }

  //If remote control enabled give user control via the Xbox controller.
  if (operationMode == REMOTECONTROL){
    xboxControl();
    Serial.println("Remote Control");
  }

  //If remote control disabled enable autonomous control
  if (operationMode == AUTONOMOUS) {
    Serial.println("Hello World");
  }

  //    if (Xbox.getButtonClick(UP, 0)) {
  //      Xbox.setLedOn(LED1, 0);
  //      Serial.println(F("Up"));
  //    }
  //    if (Xbox.getButtonClick(DOWN, 0)) {
  //      Xbox.setLedOn(LED4, 0);
  //      Serial.println(F("Down"));
  //    }
  //    if (Xbox.getButtonClick(LEFT, 0)) {
  //      Xbox.setLedOn(LED3, 0);
  //      Serial.println(F("Left"));
  //    }
  //    if (Xbox.getButtonClick(RIGHT, 0)) {
  //      Xbox.setLedOn(LED2, 0);
  //      Serial.println(F("Right"));
  //    }
  //
  //    if (Xbox.getButtonClick(START, 0)) {
  //      Xbox.setLedMode(ALTERNATING, 0);
  //      Serial.println(F("Start"));
  //    }
  //    if (Xbox.getButtonClick(BACK, 0)) {
  //      Xbox.setLedBlink(ALL, 0);
  //      Serial.println(F("Back"));
  //    }
  //    if (Xbox.getButtonClick(L3, 0))
  //      Serial.println(F("L3"));
  //    if (Xbox.getButtonClick(R3, 0))
  //      Serial.println(F("R3"));
  //
  //    if (Xbox.getButtonClick(L1, 0))
  //      Serial.println(F("L1"));
  //    if (Xbox.getButtonClick(R1, 0))
  //      Serial.println(F("R1"));
  //    if (Xbox.getButtonClick(XBOX, 0)) {
  //      Xbox.setLedMode(ROTATING, 0);
  //      Serial.print(F("Xbox (Battery: "));
  //      Serial.print(Xbox.getBatteryLevel(0)); // The battery level in the range 0-3
  //      Serial.println(F(")"));
  //    }
  //    if (Xbox.getButtonClick(SYNC, 0)) {
  //      Serial.println(F("Sync"));
  //      Xbox.disconnect(0);
  //    }
  //
  //    if (Xbox.getButtonClick(A, 0))
  //      Serial.println(F("A"));
  //    if (Xbox.getButtonClick(B, 0))
  //      Serial.println(F("B"));
  //    if (Xbox.getButtonClick(X, 0))
  //      Serial.println(F("X"));
  //    if (Xbox.getButtonClick(Y, 0))
  //      Serial.println(F("Y"));
}
