//***********************************************************************************************
// Directional Driving Functions
//***********************************************************************************************
void turnLeft()
{
  leftServo.write(135);
  rightServo.write(45);
}

void turnRight()
{
  leftServo.write(45);
  rightServo.write(135);
}

void driveForward()
{
  leftServo.write(45);
  rightServo.write(45);
}

void driveReverse()
{
  leftServo.write(135);
  rightServo.write(135);
}

//***********************************************************************************************
// Turn the robot in a random direction
//***********************************************************************************************
void driveTurn()
{
  static int turnDir = random(0, 2); //Random function chooses between min and max-1
  switch (turnDir) {
    case 0: //Turn Right
      turnRight();
      break;
    case 1: //Turn Left
      turnLeft();
      break;
  }
}
