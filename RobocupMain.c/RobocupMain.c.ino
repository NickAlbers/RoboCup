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


Servo myservoA;      // create servo object to control a servo
Servo myservoB;      // create servo object to control a servo

USB Usb;
XBOXRECV Xbox(&Usb);

void setup()
{ 
  int motorSpeed = 0;
 //Setup the Servos 
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board
  
  myservoA.attach(3);  // attaches the servo pin 3 to the servo object
  myservoB.attach(2);  // attaches the servo pin 2 to the servo object
  
  //setup the Xbox Receiver
  Serial.begin(115200);
  #if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
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
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        if (Xbox.getButtonPress(L2, i) || Xbox.getButtonPress(R2, i)) {
          Serial.print("L2: ");
          Serial.print(Xbox.getButtonPress(L2, i));
          Serial.print("\tR2: ");
          Serial.println(Xbox.getButtonPress(R2, i));
          Xbox.setRumbleOn(Xbox.getButtonPress(L2, i), Xbox.getButtonPress(R2, i), i);
        }

        if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500 || Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500 || Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
       
          //Forward and Reverse Control
          if (Xbox.getAnalogHat(LeftHatY, i) > 8000) { //7500 is default value
            myservoA.write(135);
            myservoB.write(135);
          }
          if (Xbox.getAnalogHat(LeftHatY, i) < -7500) { //-7500 is default
            myservoA.write(45);
            myservoB.write(45);
          }

          //Rotate Right and left
//          if (Xbox.getAnalogHat(LeftHatX, i) > 7500) { //7500 is default value
//            myservoA.write(135);
//            myservoB.write(45);
//          }
//          if (Xbox.getAnalogHat(LeftHatX, i) > -7500) { //7500 is default value
//            myservoA.write(45);
//            myservoB.write(135);
//          }
          if (Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500) {
            myservoA.write(90);
            myservoB.write(90);
          }
          if (Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
            myservoA.write(90);
            myservoB.write(90);
          }
          Serial.println();
        }

        if (Xbox.getButtonClick(UP, i)) {
          Xbox.setLedOn(LED1, i);
          Serial.println(F("Up"));
        }
        if (Xbox.getButtonClick(DOWN, i)) {
          Xbox.setLedOn(LED4, i);
          Serial.println(F("Down"));
        }
        if (Xbox.getButtonClick(LEFT, i)) {
          Xbox.setLedOn(LED3, i);
          Serial.println(F("Left"));
        }
        if (Xbox.getButtonClick(RIGHT, i)) {
          Xbox.setLedOn(LED2, i);
          Serial.println(F("Right"));
        }

        if (Xbox.getButtonClick(START, i)) {
          Xbox.setLedMode(ALTERNATING, i);
          Serial.println(F("Start"));
        }
        if (Xbox.getButtonClick(BACK, i)) {
          Xbox.setLedBlink(ALL, i);
          Serial.println(F("Back"));
        }
        if (Xbox.getButtonClick(L3, i))
          Serial.println(F("L3"));
        if (Xbox.getButtonClick(R3, i))
          Serial.println(F("R3"));

        if (Xbox.getButtonClick(L1, i))
          Serial.println(F("L1"));
        if (Xbox.getButtonClick(R1, i))
          Serial.println(F("R1"));
        if (Xbox.getButtonClick(XBOX, i)) {
          Xbox.setLedMode(ROTATING, i);
          Serial.print(F("Xbox (Battery: "));
          Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
          Serial.println(F(")"));
        }
        if (Xbox.getButtonClick(SYNC, i)) {
          Serial.println(F("Sync"));
          Xbox.disconnect(i);
        }

        if (Xbox.getButtonClick(A, i))
          Serial.println(F("A"));
        if (Xbox.getButtonClick(B, i))
          Serial.println(F("B"));
        if (Xbox.getButtonClick(X, i))
          Serial.println(F("X"));
        if (Xbox.getButtonClick(Y, i))
          Serial.println(F("Y"));
      }
    }
  }
} 



