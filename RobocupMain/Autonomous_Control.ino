//***********************************************************************************************
//Function allowing the robot to act autonomously
//***********************************************************************************************
void autonomousControl() {
  static int autoState = 0;
  static long nextRun = 0; 
  Serial.println("Hello World");
//  
//  //Can I run yet?
//  if (millis() < nextRun)
//    return;
//    
//  switch (autoState) {
//    case 0:
//      leftServo.write(135);
//      rightServo.write(135);
//      break;
//    case 1:
//      leftServo.write(90);
//      rightServo.write(90);
//      break;
//    case 2:
//      leftServo.write(45);
//      rightServo.write(45);
//      break;
//    case 3:
//      leftServo.write(90);
//      rightServo.write(90);
//      break;
//  }
//  
//  autoState = (autoState + 1) % 4;
//  nextRun = millis() + random(500, 4000);
}



