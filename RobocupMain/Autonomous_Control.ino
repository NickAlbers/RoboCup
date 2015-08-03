//***********************************************************************************************
//Function allowing the robot to steer autonomously
//***********************************************************************************************
void autonomousDrive()
{
  static long nextRun = 0;
  static RobotState driveState = DRIVING;
  static int turnDir = 1;

  //Checkfor collision
  if (collisionDetect() == true)
  {
    driveState = EVASIVETACTICS;
  }

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
      nextRun = millis() + random(500, 2000);
      driveTurn();
      driveState = DRIVING; //Set the next run to be a drive command
      break;
    case EVASIVETACTICS:
      Serial.println("Evading");
      nextRun = millis() + random(500, 6000);
//      evasiveTactics();
      driveState = DRIVING;
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
    return true;
  }
  else {
    return false;
  }
}








