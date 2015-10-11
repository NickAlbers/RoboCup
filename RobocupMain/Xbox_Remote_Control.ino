//***********************************************************************************************
//  Buttons in use: X, Y, A LefthatY, RightHatX
//***********************************************************************************************


//***********************************************************************************************
// Initialise Xbox Receiver
//***********************************************************************************************
void setupXboxReceiver()
{
  Serial.begin(BAUDRATE);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect
#endif
  if (Usb.Init() == -1) {
    Serial.println(F("\r\nOSC did not start"));
    //while (1); //halt
  }
  Serial.println(F("\r\nXbox Wireless Receiver Library Started"));
}

//***********************************************************************************************
// Changes from autonomous to remote control and vice versa on A "y" button press.
//***********************************************************************************************
void modeSelect(_Robot *Bagger)
{
  //Serial.println("ModeSelect");
  //Get the latest data on pressed buttons from the Xbox receiver
  Usb.Task();

  // Enable or Disable remote control when Y is pressed
  if (Xbox.XboxReceiverConnected && Xbox.Xbox360Connected[0])
  {

    if (opMode != REMOTECONTROL && Xbox.getButtonPress(X, 0))
    {
      opMode = REMOTECONTROL;
      Serial.println("Remote control enabled");
    }

    else if (opMode != AUTONOMOUS && Xbox.getButtonPress(Y, 0))
    {
      opMode = AUTONOMOUS;
      Serial.println("Autonomous mode activated");
    }

    else if (opMode != HANDBRAKE && Xbox.getButtonPress(A, 0))
    {
      opMode =  HANDBRAKE;
      Serial.println("Handbrake on");
    }
  }
}



//***********************************************************************************************
//Function to control the DC motors from an xbox controller.
//Left analog stick maps speed, right analog controls direction
//***********************************************************************************************
void xboxControl(_Robot *robot)
{
  //Get the latest data on pressed buttons from the Xbox receiver
  Usb.Task();

  //  Serial.println("Polling Xbox Controller");
  //  Serial.println("Remote Control"); Enable for debugging
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
  }

  //Sweep the servos for package collection
  if (Xbox.getButtonPress(B, 0)) {
    toggleJaws(1, 2);
  }

  //  //Toggle the tray position
  //  if (Xbox.getButtonClick(L2, 0)) {
  //    if (trayPosition == TRAYDOWN)
  //    {
  //      liftTray(42);
  //    }
  //    else if (trayPosition == TRAYUP)
  //    {
  //      lowerTray(42);
  //    }
  //  }

  if (Xbox.getButtonClick(UP, 0)) {
    liftTray(42);
  }

  if (Xbox.getButtonClick(DOWN, 0)) {
    lowerTray(42);
  }

  if (Xbox.getButtonPress(L1, 0)) {
    setupSmartServos();
  }

  if (Xbox.getButtonPress(RIGHT, 0)) {
    readIMU(robot);
  }

  if (Xbox.getButtonPress(LEFT, 0)) {
    readMagnetometer(robot);
  }
  
  if (Xbox.getButtonPress(L2, 0)) {
    Weight_GetWeight();
  }

  //    if (Xbox.getButtonPress(L2, 0)) {
  //    readIMU(&Bagger);
  //  }


  //Flash LED Green
  //  if (Xbox.getButtonPress(R1, 0)) {
  //    UpdateLED(0, 255, 0);
  //  }
  //
  //  //Flash LED red
  //  if (Xbox.getButtonPress(R2, 0)) {
  //    UpdateLED(255, 0, 0);
  //  }
  //
  //  //Flash LED blue
  //  if (Xbox.getButtonPress(R3, 0)) {
  //    UpdateLED(0, 0, 255);
  //  }
  //
  //    //Clear LED
  //  if (Xbox.getButtonPress(L3, 0)) {
  //    UpdateLED(0, 0, 0);
  //  }

}
