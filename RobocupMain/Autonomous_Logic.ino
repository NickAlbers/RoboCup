//***********************************************************************************************
//Function allowing the robot to steer autonomously
//***********************************************************************************************
void Auto_Logic(_Robot *Bagger)
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
      Motors_VariableDrive(Bagger->Speed, Forward);
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
      Auto_EvasiveManoeuvers(Bagger);
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
// Read the medium range IR sensors, and execute collision avoidance code if a collision is
// imminent, return true if an object is within "safeDistance" centimeters
//***********************************************************************************************
void Auto_CollisionDetect(_Robot *Bagger)
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

void Auto_EvasiveManoeuvers(_Robot *Bagger)
{
  //If the robot is not in a corner
  if (cornerFlag == FALSE) {
    cornerTime = millis() + CORNER_TIMEOUT;
    cornerFlag = true;
  }
  
  // Detect the direction of the imminent collision
  signed int collisionDirection = (Bagger->IRmed_L - Bagger->IRmed_R); //Work out fastest turn direction to avoid collision
  
  Serial.print("collisionDirection: ");
  Serial.println(collisionDirection, DEC);
  

  Bagger->Speed = map(min(Bagger->IRmed_L,Bagger->IRmed_R),COLLISIONDISTANCE,SAFEDISTANCE,0,MAXSPEED);

  if (millis() > cornerTime) {
    Serial.print("   ");
    Serial.print("In corner");
    
    Motors_TurnRandom();
    nextRun = millis() + random(COLLISION_MIN_TIME, COLLISION_MAX_TIME);; //Delay long enough to complete a turn
  }
  
  else {
    Serial.println("Collision!!!");
    Bagger->turnDir = (TurnDirection)(map(collisionDirection,-80,80,-90,90));
//    Serial.println(Bagger->turnDir);
    Motors_VariableDrive(Bagger->Speed, Bagger->turnDir);
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
