//***********************************************************************************************
// Check the collision sensors, then execute avoidance maneouveres THESE VALUES REQUIRE TWEAKING
// THIS FUNCTION IS BLOCKING
//***********************************************************************************************

void Maneouver2Weight(_Robot *Bagger)
{
  //  Serial.println("maneouvering to Weight");
  signed int package_xPos;
  Bagger->Speed = 50;//map(min(Bagger->Ultra_L,Bagger->Ultra_R),0,(MAX_ULTRA-DETECTION_MARGIN),MIN_COLLECT_SPEED,MAX_COLLECT_SPEED);

  if (Bagger->package_C) {
    package_xPos = ((Bagger->Ultra_L * Bagger->Ultra_L) - (Bagger->Ultra_R * Bagger->Ultra_R))  / (2 * ULTRA_OFFSET);
    Bagger->turnDir = (TurnDirection) (package_xPos / MANEOUVER2WEIGHT_CONST );


    //  Serial.print("Left \t");
    //  Serial.print(Bagger->Ultra_L);
    //  Serial.print("\t");
    //  Serial.print((Bagger->Ultra_L*Bagger->Ultra_L));
    //  Serial.print(" \t || Pos:");
    //    Serial.println(package_xPos);
    //  Serial.print(" \t || Turn:");
    //  Serial.println(Bagger->turnDir);
  }
  else if (Bagger->package_L) {
    Bagger->turnDir = (TurnDirection) (- min(Bagger->Ultra_L, Bagger->Ultra_R) * TURN_CONST);
    //Serial.println("left");
  }
  else if (Bagger->package_R) {
    Bagger->turnDir = (TurnDirection) (+ min(Bagger->Ultra_L, Bagger->Ultra_R) * TURN_CONST);
    //Serial.println("right");
  }
  //   nextRun = millis() + random(PACKAGE_MIN_TIME, PACKAGE_MAX_TIME);

  drive(Bagger->Speed, Bagger->turnDir);

  Bagger->driveState = COLLECTING;
  collectingPeriod = millis() + COLLECTION_TIME;
}

//***********************************************************************************************
// Scan for packages and inititiate relevant code
//***********************************************************************************************
void packageDetect(_Robot *Bagger)
{
  //  Serial.println("Package Detection");

  int detect_L = false;
  int detect_R = false;
  Bagger->package_C = false;
  Bagger->package_L = false;
  Bagger->package_R = false;
  detect_L = false;
  detect_R = false;



  if ( (Bagger->Ultra_L + DETECTION_MARGIN) < Bagger->Ultra_LT ) {
    detect_L = true;
  }
  //object on right???
  if ( (Bagger->Ultra_R + DETECTION_MARGIN) < Bagger->Ultra_RT ) {
    detect_R = true;
  }

  if (detect_L || detect_R) {
    Bagger->driveState = FINDWEIGHT;
  }
  else {
    Bagger->Speed = MAXSPEED;
    return;
  }

  //object in centre???
  if ( detect_L && detect_R ) {
    detect_L = false;
    detect_R = false;
    Bagger->package_C = true;
  }

  //Is that object to the left or right of the robot??
  //Allowing for further range by accounting for sensors crossing/changing sides
  else if ( ( detect_L && (Bagger->Ultra_L < ULTRA_OFFSET)) || (detect_R && (Bagger->Ultra_R > sqrt(2)*ULTRA_OFFSET))  ) {
    Bagger->package_L = true;
  }
  else if (  (detect_R && (Bagger->Ultra_R < ULTRA_OFFSET)) || (detect_L && (Bagger->Ultra_L > sqrt(2)*ULTRA_OFFSET))  ) {
    Bagger->package_R = true;
  }

  //  collectFlag = true;
  //  collectionTime = millis() + COLLECTION_DELAY;
  return;
}


//***********************************************************************************************
// Sweep the arms if a package is against the tray
//***********************************************************************************************

void detectCollection(_Robot * Bagger)
{
  if (!digitalRead(IR_CollectionSensors_3) || !digitalRead(IR_CollectionSensors_4) )
  {
    packageCollect(Bagger);
  }

  //check scales if weight collected
  //add to number of weights
  //decide to search or return to base
  //repeat opening closing arms???
  //timeout and move on if not connected
}

bool packageCollect(_Robot * Bagger)
{
  closeJaws(1, 2); //Close jaws
  delay(500);
  openJaws(1, 2);
  delay(500);
  closeJaws(1, 2);
  delay(500);
  openJaws(1, 2);


  return true;
}

//bool checkWeight(_Robot * Bagger){
//  int weightTOT = scale1.getGram() + scale2.getGram();
//}

//***********************************************************************************************
// Sweep the arms if a package is against the tray
//***********************************************************************************************

bool packageDeploy(_Robot * Bagger)
{
  openJaws(1, 2);
  liftTray(41);
  driveReverse();
  //Open arms, tip tray, drive forwards.
}

//  if ((collectFlag && !Bagger->package_C) && (millis() > collectionTime)) {     //assume package in blindspot directly in front
//    collectionTime = millis() + COLLECTION_TIME;    //pause a moment to close arms
//    collectFlag = false;
//    sweepState = SWEEPIN;
//  }
//
//  if (Bagger->package_L || Bagger->package_R || Bagger->package_C) {
//    Bagger->driveState = FINDWEIGHT;
//    return;
//  }

void checkHomeBase(_Robot *Bagger)
{
  readColourSensor(Bagger);
    if (((g / b) > 1.0) && (g > 100))  {
    UpdateLED(Bagger);
    CurrBase = BLUE_BASE;
  }
  else if (((b / r) > 1.75) && (b > g) && (b > 150)) {
    UpdateLED(Bagger);
    CurrBase = GREEN_BASE;
  }
  if (CurrBase == HomeBase)
    {
      liftTray(42);
    }
}

void setHomeBase(_Robot *Bagger)
{
  readColourSensor(Bagger);

  if (((g / b) > 1.0) && (g > 100))  {
    Serial.println("The colour is blue");
    UpdateLED(Bagger);
    HomeBase = BLUE_BASE;
    return;
  }
  else if (((b / r) > 1.75) && (b > g) && (b > 150)) {
    Serial.println("The colour is green");
    UpdateLED(Bagger);
    HomeBase = GREEN_BASE;
    return;
  }
}


