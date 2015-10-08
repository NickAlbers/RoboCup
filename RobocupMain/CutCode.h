////***********************************************************************************************
//// Changes from autonomous to remote control and vice versa on A "y" button press.
////***********************************************************************************************
//void modeSelect(_Robot *Bagger)
//{
//  //  Serial.println("Checking Operation mode");
//  // Enable or Disable remote control when Y is pressed
//  if (Xbox.XboxReceiverConnected && Xbox.Xbox360Connected[0])
//  {
//    Serial.println("1");
//    
//    if (Xbox.getButtonPress(X, 0))
//      //    if (opMode != REMOTECONTROL && Xbox.getButtonPress(X, 0))
//    {
//      opMode = REMOTECONTROL;
//      Serial.println("Remote control enabled");
//    }
//    
//    else if (Xbox.getButtonClick(Y, 0))
//      //    else if (opMode != AUTONOMOUS && Xbox.getButtonPress(Y, 0))
//    {
//      opMode = AUTONOMOUS;
//      Serial.println("Autonomous mode activated");
//    }
//    
//    else if (Xbox.getButtonPress(A, 0))
//      //    else if (opMode != HANDBRAKE && Xbox.getButtonPress(A, 0))
//    {
//      opMode = HANDBRAKE;
//      Serial.println("Handbrake on");
//    }
//    
//    else
//    {
//      //      Serial.println("No Mode Change");
//      Serial.println("6");
//    }
//  }
//}
