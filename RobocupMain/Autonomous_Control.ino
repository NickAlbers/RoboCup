//***********************************************************************************************
//Function allowing the robot to steer autonomously
//***********************************************************************************************
void autonomousDrive() 
{
  static long nextRun = 0;
  static int driveState = DRIVING; // Drive forwards first
  static int turnDir = 1;

  //Can I turn yet?
  if (millis() < nextRun) {
    return;
  }
  
  //
  else {
    switch (driveState) {
      case DRIVING:
        Serial.println("Driving");

        //Generate a time to drive for, and set the next state to be turning
        nextRun = millis() + random(500, 6000);
        driveState = TURNING;

        //Write the Full speed drive value to the motors
        leftServo.write(45);
        rightServo.write(45);
        break;

      case TURNING:
        Serial.println("Turning");
        //Generate a time to turn for, Select rotation direction
        nextRun = millis() + random(500, 2000);
        turnDir = random(0, 2); //Random function chooses between min and max-1
        driveState = DRIVING; //Set the next run to be a drive command

        switch (turnDir) {
          case 0: //Turn Right
            leftServo.write(45);
            rightServo.write(135);
            break;
          case 1: //Turn Left
            leftServo.write(135);
            rightServo.write(45);
            break;
        }
        break;
    }
  }
}


//***********************************************************************************************
//Function allowing the robot to act autonomously
//***********************************************************************************************
void autonomousControl() 
{
  static int autoState = 0;
}

//***********************************************************************************************
// Read the medium range IR sensors, and execute collision avoidance code if a collision is 
// imminent, return true if an object is within "safeDistance" centimeters
//***********************************************************************************************
bool collisionDetect() 
{
  static int collisionDistance = 100;
  collisionDistance = readIRMed();
  
  if (collisionDistance <= SAFEDISTANCE){
    return true;
  }
  else {
    return false;
  }
}

  



