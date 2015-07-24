//***********************************************************************************************
// Changes from autonomous to remote control and vice versa on A "y" button press.
//***********************************************************************************************
void modeSelect() {
  //Enable or Disable remote control when Y is pressed
  if (Xbox.XboxReceiverConnected && Xbox.Xbox360Connected[0]) {
    if (operationMode == AUTONOMOUS && Xbox.getButtonPress(X, 0)) {
      operationMode = REMOTECONTROL;
      Serial.println("Remote control enabled");
    }
    else if (operationMode == REMOTECONTROL && Xbox.getButtonPress(Y, 0))
    {
      operationMode = AUTONOMOUS;
      Serial.println("Autonomous mode activated");
    }
  }
  else {
    operationMode = AUTONOMOUS;
    Serial.println("Autonomous mode activated, no xbox detected");
  }
}
//***********************************************************************************************
//Function to control the DC motors from an xbox controller.
//Left analog stick maps speed, right analog controls direction
//***********************************************************************************************
void xboxControl() {
  Serial.println("Remote Control");
  if (Xbox.getAnalogHat(LeftHatX, 0) > 1500 || Xbox.getAnalogHat(LeftHatX, 0) < -1500
      || Xbox.getAnalogHat(LeftHatY, 0) > 1500 || Xbox.getAnalogHat(LeftHatY, 0) < -1500
      || Xbox.getAnalogHat(RightHatX, 0) > 1500 || Xbox.getAnalogHat(RightHatX, 0) < -1500
      || Xbox.getAnalogHat(RightHatY, 0) > 1500 || Xbox.getAnalogHat(RightHatY, 0) < -1500)
  {

    //Read joystick values
    int trackSpeed = Xbox.getAnalogHat(LeftHatY, 0);
    int trackDiff = Xbox.getAnalogHat(RightHatX, 0);

    //Map to motor ranges
    //Flip 135 and 45 if the chasis is flipped
    trackSpeed  = map(trackSpeed, -32767, 32767, 135, 45);
    trackDiff = map(trackDiff, -32767, 32767, 45, -45);

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
    Serial.println(trackLeft);
    Serial.println(trackRight);
  }
}
//***********************************************************************************************
