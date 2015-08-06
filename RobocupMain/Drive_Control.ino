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
//  leftTrayServo.attach(33);
//  rightTrayServo.attach(32);
}

//***********************************************************************************************
// Directional Driving Functions
//***********************************************************************************************

//left
void turnLeft()
{
  leftServo.write((45*SPEED_PERC)/100 + 90);
  rightServo.write(90 - (45*SPEED_PERC)/100);
}

//Right
void turnRight()
{
  leftServo.write(90 - (45*SPEED_PERC)/100);
  rightServo.write((45*SPEED_PERC)/100 + 90);
}

//Forward
void driveForward()
{
  leftServo.write(90 - (45*SPEED_PERC)/100);
  rightServo.write(90 - (45*SPEED_PERC)/100);
}

//Reverse
void driveReverse()
{
  leftServo.write((45*SPEED_PERC)/100 + 90);
  rightServo.write((45*SPEED_PERC)/100 + 90 );
}

//Stop
void driveStop()
{
  leftServo.write(90);
  rightServo.write(90);
}

//***********************************************************************************************
// Turn the robot in a specified direction
//***********************************************************************************************
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
