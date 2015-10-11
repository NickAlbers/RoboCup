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

  leftServo.attach(3);  // attaches the servo pin 3 to the servo object
  rightServo.attach(2);  // attaches the servo pin 2 to the servo object
}

//***********************************************************************************************
// Directional Driving Functions
//***********************************************************************************************

/*Function: driveStop()
 *Writes the stop speed to the motors
 */
 
void driveStop()
{
  leftServo.write(90);
  rightServo.write(90);
}

/*Function: turnRandom()
 * Picks a random direction, and rotates in that direction for a random time
 */
void turnRandom()
{
  static int rand;
  rand = random(0, 2);//Random function chooses between min and max-1
  if (rand == 0) {
    //        Bagger->turnDir = Left;
    turnRight();
  }
  else if (rand == 1) {
    turnLeft();
    //        Bagger->turnDir = Right;
  }
}

//***********************************************************************************************
// Turn the robot in a specified direction
//***********************************************************************************************

//left
void turnLeft()
{
  leftServo.write(135);
  rightServo.write(45);
}

//Right
void turnRight()
{
  leftServo.write(45);
  rightServo.write(135);
}

//Forward
void driveForward()
{
  leftServo.write(45);
  rightServo.write(45);
}

//Reverse
void driveReverse()
{
  leftServo.write(135);
  rightServo.write(135);
}

/*Function: drive(int Speed, TurnDirection angle)
 * Maps the Speed percentage and Angle to the relevant maximum and minimum values,
 * checks that they are outside the deadband, and then write the values to the motors.
 * Driving them at the calculated speed to implement steering.
 */
void drive(int Speed, TurnDirection angle)
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
