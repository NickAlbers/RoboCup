//***********************************************************************************************
//Function allowing the robot to steer autonomously
//***********************************************************************************************
void autonomousDrive()
{
  static long nextRun = 0;
  static RobotState driveState = DRIVING;
  static int turnDir = 1;

  //Can I turn yet? Check for the run time and whether or not evasive tactics is enabled
  if ((millis() < nextRun) && (driveState != EVASIVETACTICS)) {
    return;
  }

  switch (driveState) {
    case DRIVING:
      Serial.println("Driving");
      //Generate a time to drive for, and set the next state to be turning
      nextRun = millis() + random(500, 6000);
      driveForward();
      driveState = TURNING; // Set the next run to be driving forwards
      break;

    case TURNING:
      Serial.println("Turning");
      //Generate a time to turn for
      turnDir = random(0, 2); //Random function chooses between min and max-1
      nextRun = millis() + random(500, 2000);
      driveTurn(turnDir);
      driveState = DRIVING; //Set the next run to be a drive command
      break;
  }
}

//***********************************************************************************************
// Read the medium range IR sensors, and execute collision avoidance code if a collision is
// imminent, return true if an object is within "safeDistance" centimeters
//***********************************************************************************************
bool collisionDetect()
{
  static int collisionDistance1 = readIRMed(A0);
  static int collisionDistance2 = readIRMed(A1);

  if ((collisionDistance1 || collisionDistance2) <= SAFEDISTANCE) {
    Serial.println("COLLISION DETECTED");
    evasiveManeouvers();
    return true;
  }
  else {
    return false;
  }
}

//***********************************************************************************************
// Scan for packages and inititiate relevant code
//***********************************************************************************************
void packageDetect()
{
  return;
}

//***********************************************************************************************
// Check the collision sensors, then execute avoidance maneouveres THESE VALUES REQUIRE TWEAKING
// THIS FUNCTION IS BLOCKING
//***********************************************************************************************

void evasiveManeouvers()
{
  Serial.println("EVASIVEMANOUEVErs");
  //Read the collision detection sensors and guess the shortest path out of the collision
  int leftSensor = readIRMed(A0);
  int rightSensor = readIRMed(A1);

  int collisionDirection = (leftSensor - rightSensor);

  if (collisionDirection < 0) //Right sensor reads further away than left sensor
  {
    while (collisionDetect() == true) //Continue turning until the obstacle is avoided
    {
      driveTurn(1);
    }
  }
  else if (collisionDirection >= 0) //Left sensor reads further away than right sensor
  {
    while (collisionDetect() == true) //Continue turning until the obstacle is avoided
    {
      driveTurn(0);
    }
  }
  driveState = DRIVING;
}













