


//***********************************************************************************************
//Function allowing the robot to steer autonomously
//***********************************************************************************************
void autonomousDrive(_Robot *Bagger)
{
  //Serial.println("AutonomousDrive");
  
  static TurnDirection turnDir = Left;
  long rand;
  
  //Can I turn yet? Check for the run time and whether or not evasive tactics is enabled
  if (  (millis() < nextRun) && (Bagger->driveState != EVASIVETACTICS) && (Bagger->driveState != FINDWEIGHT)  ) {
    return;
  }

  switch (Bagger->driveState) {
    case DRIVING:
      Serial.println("Driving");
      //Generate a time to drive for, and set the next state to be turning
      nextRun = millis() + random(DRIVING_MIN_TIME, DRIVING_MAX_TIME); 
      drive(Bagger->Speed, Forward);
      //drive(0, Forward);
      //Bagger->driveState = TURNING; // Set the next run to be driving forwards
      break;

    case TURNING:
      Serial.println("Turning");

      nextRun = millis() + random(TURNING_MIN_TIME, TURNING_MAX_TIME); //Generate a time to turn for
      //turnRandom();
      Bagger->driveState = DRIVING; //Set the next run to be a drive command
      break;
      
    case EVASIVETACTICS:
      //Serial.println("Avoiding Object");
      evasiveManeouvers(Bagger);
      Bagger->driveState = DRIVING;
      break;

    case FINDWEIGHT:
      //Serial.println("Finding Package");
      Maneouver2Weight(Bagger);
      Bagger->driveState = DRIVING;
      break;
  }
}


//***********************************************************************************************
// This function reads all sensors and stores them in the robot struct
//***********************************************************************************************

void updateSensors(_Robot *Bagger)
{
  //int tick = millis();
   //Serial.println("Update Sensors");
  //Bagger->IRlong_L = readIRMed(IRlong_L_Pin);
  //Bagger->IRlong_R = readIRMed(IRlong_R_Pin);
  
  
  Bagger->IRmed_L = readIRMed(IRmed_L_Pin);
  Bagger->IRmed_R = readIRMed(IRmed_R_Pin);
  
  
  Bagger->Ultra_L = Ultra_L.ping_cm();
  Bagger->Ultra_R = Ultra_R.ping_cm();
  Bagger->Ultra_LT = Ultra_LT.ping_cm();
  Bagger->Ultra_RT = Ultra_RT.ping_cm();

  if(Bagger->Ultra_L==0)Bagger->Ultra_L=MAX_ULTRA;
  if(Bagger->Ultra_R==0)Bagger->Ultra_R=MAX_ULTRA;
  if(Bagger->Ultra_LT==0)Bagger->Ultra_LT=MAX_ULTRA;
  if(Bagger->Ultra_RT==0)Bagger->Ultra_RT=MAX_ULTRA;
//  Serial.print(Bagger->Ultra_L);
//  Serial.print("\t | \t");
//  Serial.print(Bagger->Ultra_LT);
//  Serial.print("\t || \t");
//  Serial.print(Bagger->Ultra_R);
//  Serial.print("\t | \t");
//  Serial.println(Bagger->Ultra_RT);
  //int tock = millis();
  //Serial.println(tock-tick);
}

//***********************************************************************************************
// Read the medium range IR sensors, and execute collision avoidance code if a collision is
// imminent, return true if an object is within "safeDistance" centimeters
//***********************************************************************************************
void collisionDetect(_Robot *Bagger)
{
  //Serial.println("Collision Detect");
  if ((Bagger->IRmed_L  <= SAFEDISTANCE) || (Bagger->IRmed_R  <= SAFEDISTANCE)) {
    Bagger->driveState = EVASIVETACTICS;
//    Serial.println("Collision");
    return;
  }
  else Bagger->Speed = MAXSPEED;
  cornerFlag = false;
}

//***********************************************************************************************
// Check the collision sensors, then execute avoidance maneouveres THESE VALUES REQUIRE TWEAKING
// THIS FUNCTION IS BLOCKING
//***********************************************************************************************

void evasiveManeouvers(_Robot *Bagger)
{
  if (!cornerFlag) {
    cornerTime = millis() + CORNER_TIMEOUT;
    cornerFlag = true;
  }
  
  signed int collisionDirection = (Bagger->IRmed_L - Bagger->IRmed_R); //Work out fastest turn direction to avoid collision

  Bagger->Speed = map(min(Bagger->IRmed_L,Bagger->IRmed_R),COLLISIONDISTANCE,SAFEDISTANCE,0,MAXSPEED);
  
  
  
  if (millis() > cornerTime) {
    Serial.print("   ");
    Serial.print("In corner");
    turnRight();
  }
  
  else {
//    Serial.println("Collision!!!");
    Bagger->turnDir = (TurnDirection)(map(collisionDirection,-80,80,-90,90));
//    Serial.println(Bagger->turnDir);
    drive(Bagger->Speed, Bagger->turnDir);
  }
  
  
  
//  else if (collisionDirection < 0) //Left sensor reads further away than right sensor
//  {
//    Serial.println("Collision Right");
//    turnLeft();
//    nextRun = millis() + random(COLLISION_MIN_TIME, COLLISION_MAX_TIME);
//  }
//  else if (collisionDirection >= 0) //Right sensor reads further away than left sensor
//  {
//    Serial.println("Collision Right");
//    turnRight();
//    nextRun = millis() + random(COLLISION_MIN_TIME, COLLISION_MAX_TIME);
//  }
 
}
