#include "Herkulex.h"
int Smart_1=1; //motor ID - verify your ID !!!!
int Smart_2=2;
/*
0xfd or 253 is the default
0xfe or 254 is broadcast, ie all motors
*/
 
void setupSmartServos() 
{
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board
  
  Herkulex.beginSerial2(115200); //open serial port 2 to talk to the motors
  Herkulex.reboot(1);            //reboot motor
  Herkulex.reboot(2);            //reboot motor
  delay(500);
  
  Herkulex.initialize();         //initialize motors
}
 
void moveSmartServo(int servo)
{
  Herkulex.moveOneAngle(servo, -100, 1000, LED_BLUE); //move motor backward
  delay(1200);
  Herkulex.moveOneAngle(servo, 100, 1000, LED_GREEN); //move motor forward
  delay(1200);   
}

