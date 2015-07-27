//***********************************************************************************************
//Function allowing the robot to act autonomously
//***********************************************************************************************
void autonomousControl() {
  static int autoState = 0;
  static long nextRun = 0;
  Serial.println("Hello World");
  //
  //  Can I turn yet?
  //  if (millis() < nextTurn)
  //    return;
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
  //    case 3:
  //      leftServo.write(90);
  //      rightServo.write(90);
  //      break;
  //  }
  //
  //  autoState = (autoState + 1) % 4;
  //  nextTurn = millis() + random(500, 4000);
}



