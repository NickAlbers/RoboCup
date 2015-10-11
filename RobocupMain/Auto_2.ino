void RandomDrive (void)
{
  static int16_t PackageCollectedTime = 0;
  
  
  if ((millis() > (PackageCollectedTime + JAWSCLOSEPERIOD)) && (JawsClosedFlag == TRUE))
  {
    Jaws_Open();
  }

  Sensors_UpdateAll()
  Bagger->PackageDetect = DetectPackage();

  if (Bagger->PackageDetected == TRUE)
  {
    NavigateToWeight();
    {
      if (WeightInCollectionZone == TRUE)
      {
        CollectWeight;
        Bagger->JawsClosedFlag = TRUE; //The jaws are closed
        Bagger->PackageCount++;
        Bagger->PackageDetected = FALSE;
        PackageCollectedTime = millis();
      }
    }
  }
  if (CollisionDetect() == TRUE)
  {
    //Execute avoidance code
    CollisionAvoidance();
    /*While ((Left_IR_Sensor || Right_IR_Sensor) < CollisionRange);
     * If (LeftSensor < Right Sensor)
     *turnRight(10 degrees);
     *else if Right Sensor LeftSensor
     *turnLeft (10degrees);
     *
     */
  }
  if (packageCount >= 3)
  {
    //Find home
    Home_Angle = Gyro_Read();
    //While the home angle is outside -20 and +20 degrees
    
    //Aim for Home
    while ((Home_Angle < -20) || (Home_Angle > 20))
    {
      turnRight(); //Rotate right until the conditions are met
      delay(10);
      driveStop();
      Home_Angle = Gyro_Read();
    }
    
    HomeFindingLoop();
    {
      driveForwards();
      Sensors_UpdateAll();
      if (CollisionDetect() == TRUE)
      {
        //Execute Avoidance Code
      }
      AimForHome();
  }
}



