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
  static long nextTurn = 0;
  //  //Can I turn yet?
  //  if (millis() < nextTurn)
  //    return;
  
  //      turnVal = random(-45, 45);
  //      leftServo.write(turnVal);
  //      rightServo.write(-turnVal);
  //      leftServo.write(135);
  //      rightServo.write(135);
//  switch (driveState) {
//    case TURNING:
//      turnTime = random(200, 1000);
//      turnDir = random(1, 2);
//      
//      if (turnDir == 1) { //Turn right
//        leftServo.write(45);
//        rightServo.write(-45);
//      }
//      else if (turnDir == 2) { //Turn left
//        leftServo.write(-45);
//        rightServo.write(45);
//      }
//     case DRIVING:
//
//    break;
//    case DRIVING:
//    break;
//    
//  }
      
    

  //  nextTurn = millis() + random(500, 4000);
}


