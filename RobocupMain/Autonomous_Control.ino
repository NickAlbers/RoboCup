
//***********************************************************************************************
//Function allowing the robot to steer autonomously
//***********************************************************************************************
void autonomousDrive(_Robot *Bagger)
{
  static TurnDirection turnDir = Left;
  long rand;
  //Can I turn yet? Check for the run time and whether or not evasive tactics is enabled
  //  if ((millis() < nextRun) && ((Bagger->driveState != EVASIVETACTICS) || (Bagger->driveState != FINDWEIGHT))) {
  if ((millis() < nextRun) && ((Bagger->driveState != EVASIVETACTICS))) {
    return;
  }

  switch (Bagger->driveState) {
    case DRIVING:
      Serial.println("Driving");
      //Generate a time to drive for, and set the next state to be turning
      nextRun = millis() + random(DRIVING_MIN_TIME, DRIVING_MAX_TIME);
      //      drive(Bagger->Speed, Forward);
      driveForward();
      Bagger->driveState = TURNING; // Set the next run to be driving forwards
      break;

    case TURNING:
      Serial.println("Turning");
      
      nextRun = millis() + random(TURNING_MIN_TIME, TURNING_MAX_TIME); //Generate a time to turn for
      turnRandom();
      //      drive(0, Bagger->turnDir);
      Bagger->driveState = DRIVING; //Set the next run to be a drive command
      break;

    case EVASIVETACTICS:
      Serial.print("Avoiding Object");
      evasiveManeouvers(Bagger);
      Bagger->driveState = DRIVING;

//    case FINDWEIGHT:
//      Serial.print("Finding Package");
//      Maneouver2Weight(Bagger);
//      Bagger->driveState = DRIVING;
  }
}


//***********************************************************************************************
// This function reads all sensors and writes them into an averaging circular buffer
//***********************************************************************************************

void updateSensors(_Robot *Bagger)
{

  Bagger->IRlong_L = readIRMed(IRlong_L_Pin);
  Bagger->IRlong_R = readIRMed(IRlong_R_Pin);
  Bagger->IRmed_L = readIRMed(IRmed_L_Pin);
  Bagger->IRmed_R = readIRMed(IRmed_R_Pin);
  Bagger->Ultra_L = readUltra(Ultra_L_trigPin, Ultra_L_echoPin);
  Bagger->Ultra_R = readUltra(Ultra_R_trigPin, Ultra_R_echoPin);

}

//***********************************************************************************************
// Read the medium range IR sensors, and execute collision avoidance code if a collision is
// imminent, return true if an object is within "safeDistance" centimeters
//***********************************************************************************************
void collisionDetect(_Robot *Bagger)
{
  if ((Bagger->IRmed_L  <= SAFEDISTANCE) || (Bagger->IRmed_R  <= SAFEDISTANCE)) {
    Bagger->driveState = EVASIVETACTICS;
    return;
  }
}

//***********************************************************************************************
// Scan for packages and inititiate relevant code
//***********************************************************************************************
void packageDetect(_Robot *Bagger)
{
  //if ultraSound detects but IR does not(at the same distance).
  static int object_L = false;
  static int object_R = false;
  static int object_C = false;
  Bagger->package_C = false;
  Bagger->package_L = false;
  Bagger->package_R = false;

  // object in sensor range ??
  if (Bagger->Ultra_L < (Bagger->IRmed_L - PACKAGE_IDENT_CONST)) {     //'PACKAGE_CONST' to try account for sensors not being calibrated and sharp having narrower
    object_L = true;  }
  if (Bagger->Ultra_R < (Bagger->IRmed_R - PACKAGE_IDENT_CONST)) {
    object_R = true;  }
  if (object_L == true && object_R == true) {
    object_C = true;  }

  //Is that object to the left or right of the robot??
  if (object_C) {
    Bagger->package_C = true;
  }
  else if (  (object_L && (Bagger->Ultra_L < ULTRA_OFFSET))||(object_R && (Bagger->Ultra_R > sqrt(2)*ULTRA_OFFSET))  ) {
    Bagger->package_L = true;
  }
  else if (  (object_R && (Bagger->Ultra_R < ULTRA_OFFSET))||(object_L && (Bagger->Ultra_L > sqrt(2)*ULTRA_OFFSET))  ) {
    Bagger->package_R = true;
  }
  

  if (object_L || object_R || object_C) {
    Bagger->driveState = FINDWEIGHT;  }

//  Serial.print("| ");
//  Serial.print(object_L);
//  Serial.print(" ");
//  Serial.print(object_R);
//  Serial.print(" ");
//  Serial.print(object_C);
//  Serial.println(" |  ");
//  return;
}

//***********************************************************************************************
// Check the collision sensors, then execute avoidance maneouveres THESE VALUES REQUIRE TWEAKING
// THIS FUNCTION IS BLOCKING
//***********************************************************************************************

void evasiveManeouvers(_Robot *Bagger)
{
  static long cornerTime = millis() + CORNER_TIMEOUT;
  signed int collisionDirection = (Bagger->IRmed_L - Bagger->IRmed_R); //Work out fastest turn direction to avoid collision

  if (collisionDirection < 0) //Left sensor reads further away than right sensor
  {
    turnLeft();
    nextRun = millis() + random(COLLISION_MIN_TIME, COLLISION_MAX_TIME);
  }
  else if (collisionDirection >= 0) //Right sensor reads further away than left sensor
  {
    turnRight();
    nextRun = millis() + random(COLLISION_MIN_TIME, COLLISION_MAX_TIME);
  }
  driveState = DRIVING; //The next run should be to drive forwards
  
}



//***********************************************************************************************
// Check the collision sensors, then execute avoidance maneouveres THESE VALUES REQUIRE TWEAKING
// THIS FUNCTION IS BLOCKING
//***********************************************************************************************

void Maneouver2Weight(_Robot *Bagger)
{
  signed int package_xPos;
  
  if (Bagger->package_C) {
     package_xPos = ((Bagger->Ultra_L)^2 - (Bagger->Ultra_R)^2)  / (4*ULTRA_OFFSET);
     Bagger->turnDir = (TurnDirection) (package_xPos * MANEOUVER_CONST);
  }
  else if (Bagger->package_L) {
    Bagger->turnDir = Left;     //Maybe should use some proportional constant here!
  }    
//  else (Bagger->package_R) {
//    Bagger->turnDir = Right;      //and here...
//  }
  
  drive(Bagger->Speed, Bagger->turnDir);
  
//  if (PackageDirection < 0) //Left sensor reads further away than right sensor
//  {
//    driveTurn(Right);
//    nextRun = millis() + random(PACKAGE_MIN_TIME, PACKAGE_MAX_TIME);
//  }
//  else if (PackageDirection >= 0) //Right sensor reads further away than left sensor
//  {
//    driveTurn(Left);
//    nextRun = millis() + random(PACKAGE_MIN_TIME, PACKAGE_MAX_TIME);
//  }

}
