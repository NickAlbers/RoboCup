//***********************************************************************************************
// Useing port S1 and channels S1 and S2 to Motors_VariableDrive the two motors on the robot.
// The motors must be connected through the Sabertooth Motors_VariableDriver.
// The sabertooth must be in mode Microcontroller pulses, independent linear control mode.
// 1000us to 2000us control the speed and direction. 1500us is stop.
// Any speed outside this range will be ignored.
//***********************************************************************************************
void setupDCMotors()
{
  //Setup the Servos

  leftServo.attach(3);  // attaches the servo pin 3 to the servo object
  rightServo.attach(2);  // attaches the servo pin 2 to the servo object
}

//***********************************************************************************************
// Directional Driving Functions
//***********************************************************************************************

/*Function: Motors_DriveStop()
 *Writes the stop speed to the motors
 */
 
void Motors_DriveStop()
{
  leftServo.write(90);
  rightServo.write(90);
}

/*Function: Motors_TurnRandom()
 * Picks a random direction, and rotates in that direction for a random time
 */
void Motors_TurnRandom()
{
  static int rand;
  rand = random(0, 2);//Random function chooses between min and max-1
  if (rand == 0) {
    //        Bagger->turnDir = Left;
    Motors_TurnRight();
  }
  else if (rand == 1) {
    Motors_TurnLeft();
    //        Bagger->turnDir = Right;
  }
}

//***********************************************************************************************
// Turn the robot in a specified direction
//***********************************************************************************************

//left
void Motors_TurnLeft()
{
  leftServo.write(135);
  rightServo.write(45);
}

//Right
void Motors_TurnRight()
{
  leftServo.write(45);
  rightServo.write(135);
}

//void Motors_TurnRightSlow();
//{
//  leftServo.write(70);
//  rightServo.write(110);
//}

//Forward
void Motors_DriveForward()
{
  leftServo.write(45);
  rightServo.write(45);
}

//Reverse
void Motors_DriveReverse()
{
  leftServo.write(135);
  rightServo.write(135);
}

/*Function: Motors_VariableDrive(int Speed, TurnDirection angle)
 * Maps the Speed percentage and Angle to the relevant maximum and minimum values,
 * checks that they are outside the deadband, and then write the values to the motors.
 * Driving them at the calculated speed to implement steering.
 */
void Motors_VariableDrive(int Speed, TurnDirection angle)
{
  //Map to motor ranges
  //Flip 135 and 45 if the chasis is flipped
  int trackSpeed  = map(Speed, -100, 100, 135, 45);
  int trackDiff = map(angle, Left, Right, 45, -45);

  //Deadband for Trackspeeds between 85 and 95
  if (trackSpeed < 100 && trackSpeed > 80) {
    trackSpeed = 90;
  }

  //Right on the RightHatX will increase left track speed and
  //slow right track, vice versa for the other direction
  int trackLeft = trackSpeed + trackDiff;
  int trackRight = trackSpeed - trackDiff;

  //Write output values to the motor
  leftServo.write(trackLeft);
  rightServo.write(trackRight);
}
