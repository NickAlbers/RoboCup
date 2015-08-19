


//***********************************************************************************************
// Check the collision sensors, then execute avoidance maneouveres THESE VALUES REQUIRE TWEAKING
// THIS FUNCTION IS BLOCKING
//***********************************************************************************************

void Maneouver2Weight(_Robot *Bagger)
{
  signed int package_xPos;

  if (Bagger->package_C) {
    //     package_xPos = ((Bagger->Ultra_L)^2 - (Bagger->Ultra_R)^2)  / (2*ULTRA_OFFSET);
    //     Bagger->turnDir = (((Bagger->Ultra_L)^2 - (Bagger->Ultra_R)^2)  / (2*ULTRA_OFFSET)) * MANEOUVER2WEIGHT_CONST);
    Bagger->turnDir = Forward;
    Serial.println("forward");
  }
  else if (Bagger->package_L) {
    Bagger->turnDir = (TurnDirection) - 25;   //Maybe should use some proportional constant here!
    Serial.println("left");
  }
  else if (Bagger->package_R) {
    Bagger->turnDir = (TurnDirection) + 25;      //and here...
    Serial.println("right");
  }
  nextRun = millis() + random(PACKAGE_MIN_TIME, PACKAGE_MAX_TIME);

  drive(Bagger->Speed, Bagger->turnDir);
  Bagger->driveState = DRIVING;
}

//***********************************************************************************************
// Scan for packages and inititiate relevant code
//***********************************************************************************************
void packageDetect(_Robot *Bagger)
{
  Bagger->package_C = false;
  Bagger->package_L = false;
  Bagger->package_R = false;

  //if ultraSound detects but IR does not(at the same distance).
  //object on left???

  if ( (Bagger->Ultra_L < ULTRA_OFFSET) && (Bagger->Ultra_L < (Bagger->IRmed_L - PACKAGE_IDENT_CONST)) ) {
    Bagger->package_L = true;
    //Sehhrial.println("Left");
  }

  //object on right???
  if ( (Bagger->Ultra_R < ULTRA_OFFSET) && (Bagger->Ultra_R < (Bagger->IRmed_R - PACKAGE_IDENT_CONST)) ) {
    Bagger->package_R = true;
    //Serial.println("Right");
  }

  //object in centre???
  if ( Bagger->package_L && Bagger->package_R ) {
    Bagger->package_L = false;
    Bagger->package_R = false;
    Bagger->package_C = true;
    collectFlag = true;
    collectionTime = millis() + COLLECTION_DELAY;
    //Serial.print("   ");
    //Serial.println("Centre");

  }
  if (Bagger->package_L || Bagger->package_R) {
    Bagger->driveState = FINDWEIGHT;
  }

  //  //Is that object to the left or right of the robot??
  //  //Allowing for further range by accounting for sensors crossing/changing sides
  //  if (object_C) {
  //    Bagger->package_C = true;
  //  }
  //  else if (  (object_L && (Bagger->Ultra_L < ULTRA_OFFSET))||(object_R && (Bagger->Ultra_R > sqrt(2)*ULTRA_OFFSET))  ) {
  //    Bagger->package_L = true;
  //  }
  //  else if (  (object_R && (Bagger->Ultra_R < ULTRA_OFFSET))||(object_L && (Bagger->Ultra_L > sqrt(2)*ULTRA_OFFSET))  ) {
  //    Bagger->package_R = true;
  //  }


  //  Serial.print("| ");
  //  Serial.print(object_L);
  //  Serial.print(" ");
  //  Serial.print(object_R);
  //  Serial.print(" ");
  //  Serial.print(object_C);
  //  Serial.println(" |  ");
  return;
}


//***********************************************************************************************
// Sweep the arms if a package is against the tray
//***********************************************************************************************

bool packageCollect(_Robot * Bagger)
{
  //Drive forwards until package collected
  driveForward();

  //Wait until the package is against the tray to sweep
  if (millis() < collectionTime)
  {
    return false;
  }

  //Close jaws, clear collection flag, and set
  closeJaws(1, 2); //Close jaws
  collectFlag = false;
  Bagger->packageCount ++;
  return true;
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

