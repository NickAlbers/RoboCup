//***********************************************************************************************
//Function allowing the robot to act autonomously
//***********************************************************************************************
void autonomousControl() {
  static int autoState = 0;

  Serial.println("Hello World");
  //
  //  //Can I see a package?
  //    //autoState = GETPACKAGE
  //  //Can i detect an obstacle?
  //    //autoState = AVOIDOBSTACLE

  //
  //  switch (autoState) {
  //    case 0:
  //      leftServo.write(135);
  //      rightServo.write(135);
  //      break;
  //    case 1:
  //      turnVal = random(-45, 45);
  //      leftServo.write(turnVal);
  //      rightServo.write(-turnVal);
  //      break;
  //    case 2:
  //      leftServo.write(45);
  //      rightServo.write(45);
  //      break;
  //    case GETPACKAGE:
  //      Serial.println("Package detected, collection mechanism engaged");
  //      break;
  //    case AVOIDOBSTACLE:
  //      Serial.println("Obstacle detected, evasive maneouvers");
  //      break;
  //  }
  //
  //  autoState = (autoState + 1) % 4; // Wraps state machine to 0

}

//***********************************************************************************************
//Function allowing the robot to steer autonomously
//***********************************************************************************************
void autonomousDrive() {
  static long nextRun = 0;
  
  //Can I turn yet?
  if (millis() < nextRun) {
    return
  }

  switch (driveState) {
    case TURNING:

      nextRun = random(200, 1000); //Generate a time to turn for
      int turnDir = random(1, 2); // Select rotation direction

      if (turnDir == 1) { //Turn right
        leftServo.write(45);
        rightServo.write(-45);
      }
      else if (turnDir == 2) { //Turn left
        leftServo.write(-45);
        rightServo.write(45);
      }

      driveState = DRIVING; //Set the next run to be a drive command
    case DRIVING:
      leftServo.write(135);
      rightServo.write(135);

      //Generate a time to drive for, and set the next state to be turning
      nextRun = random(500, 4000);
      driveState = TURNING;
      break;
  }
}


