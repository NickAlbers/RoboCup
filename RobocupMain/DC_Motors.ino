//***********************************************************************************************
// Useing port S1 and channels S1 and S2 to drive the two motors on the robot.
// The motors must be connected through the Sabertooth driver.
// The sabertooth must be in mode Microcontroller pulses, independent linear control mode.
// 1000us to 2000us control the speed and direction. 1500us is stop.
// Any speed outside this range will be ignored.
//***********************************************************************************************
void setupDCMotors()
{
  //Setup the Servos
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board

  leftServo.attach(3);  // attaches the servo pin 3 to the servo object
  rightServo.attach(2);  // attaches the servo pin 2 to the servo object
}
