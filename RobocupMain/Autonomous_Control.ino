
static long nextRun = 0;
//***********************************************************************************************
//Function allowing the robot to steer autonomously
//***********************************************************************************************
void autonomousDrive(_Robot *Bagger)
{

  static TurnDirection turnDir = Left;
  long rand;
  //Can I turn yet? Check for the run time and whether or not evasive tactics is enabled
  if ((millis() < nextRun) && (Bagger->driveState != EVASIVETACTICS)) {
    return;
  }
  

  switch (Bagger->driveState) {
    case DRIVING:
      Serial.println("Driving");
      //Generate a time to drive for, and set the next state to be turning
      nextRun = millis() + random(1000, 6000);
      driveForward();
      Bagger->driveState = TURNING; // Set the next run to be driving forwards
      break;

    case TURNING:
      Serial.println("Turning");
      //Generate a time to turn for
      rand = random(0, 2);
      if (rand==0){ 
        turnDir = Left;
      } 
      else if(rand==1){
        turnDir = Right;
      }//Random function chooses between min and max-1
      
      nextRun = millis() + random(1000, 3000);
      driveTurn(turnDir);
      Bagger->driveState = DRIVING; //Set the next run to be a drive command
      break;
      
    case EVASIVETACTICS:
    Serial.println("Avoiding Object");
      evasiveManeouvers(Bagger);
  }
}

//***********************************************************************************************
// Read the medium range IR sensors, and execute collision avoidance code if a collision is
// imminent, return true if an object is within "safeDistance" centimeters
//***********************************************************************************************
void collisionDetect(_Robot *Bagger)
{
//  static int collisionDist1 = avg_Circ_Buff(irMedLeftBuff);
//  static int collisionDist2 = avg_Circ_Buff(irMedRightBuff);      //Already average from sharp library and only accepting readings that are within 93% of the average


  
  if ((Bagger->IRmed_L  <= SAFEDISTANCE) || (Bagger->IRmed_R  <= SAFEDISTANCE)) {
    //Serial.println("COLLISION DETECTED");
    Bagger->driveState = EVASIVETACTICS;
    return;
  }
  else {
    Bagger->driveState = DRIVING;
    return;
  }
}

//***********************************************************************************************
// Scan for packages and inititiate relevant code
//***********************************************************************************************
void packageDetect(_Robot *Bagger)
{
  //if ultraSound detects but IR does not(at the same distance).
  return;
}

//***********************************************************************************************
// Check the collision sensors, then execute avoidance maneouveres THESE VALUES REQUIRE TWEAKING
// THIS FUNCTION IS BLOCKING
//***********************************************************************************************

void evasiveManeouvers(_Robot *Bagger)
{
  static long nextRun = 0;
//  Serial.println("");
//  Serial.println("EVASIVE MANOUEVERS");
  //Read the collision detection sensors and guess the shortest path out of the collision
//  int leftSensor = avg_Circ_Buff(irMedLeftBuff);
//  int rightSensor = avg_Circ_Buff(irMedRightBuff);

  signed int collisionDirection = (Bagger->IRmed_L - Bagger->IRmed_R); //Work out fastest turn direction to avoid collision
  
  Serial.println(Bagger->IRmed_L);
  Serial.print("  ");
  Serial.print(Bagger->IRmed_R);
  Serial.print("    Collision Direction: ");
  Serial.println(collisionDirection);

  if (collisionDirection < 0) //Right sensor reads further away than left sensor
  {
    driveTurn(Left);
    nextRun = millis() + random(500, 1000);
    Serial.println("LEFT");
  }
  else if (collisionDirection >= 0) //Left sensor reads further away than right sensor
  {
    driveTurn(Right);
    nextRun = millis() + random(500, 1000);
    Serial.println("RIGHT");
  }
  //driveState = DRIVING; //The next run should be to drive forwards
}


//***********************************************************************************************
// This function reads all sensors and writes them into an averaging circular buffer
//***********************************************************************************************

void updateSensors(_Robot *Bagger)
{
//readSensor(readIRMed(A0), irMedLeftBuff);
//readSensor(readIRMed(A1), irMedRightBuff);

  Bagger->IRlong_L = readIRMed(IRlong_L_Pin);
  Bagger->IRlong_R = readIRMed(IRlong_R_Pin);
  Bagger->IRmed_L = readIRMed(IRmed_L_Pin);
  Bagger->IRmed_R = readIRMed(IRmed_R_Pin);
  //Bagger->Ultra_L = readUltra(Ultra_L_trigPin, Ultra_L_echoPin);
  //Bagger->Ultra_R = readUltra(Ultra_R_trigPin, Ultra_R_echoPin);
  
//  
//  Serial.print(Bagger->IRmed_L);
//  Serial.print("  ");
//  Serial.println(Bagger->IRmed_R);
}

//void readSensor(int sensor, circBuf_t buffer)
//{
//  buffer.data[irMedLeftBuff.windex] = (int) sensor;
//  buffer.windex ++; // Incremeant the write pointer
//  if (buffer.windex >= buffer.size) // Wrap the buffer if its reached the end
//    buffer.windex = 0;
//}
//
//int avg_Circ_Buff(circBuf_t buffer)
//{
//  //Average the values in the buffer
//  int avg;
//  int sum;
//  unsigned int i;
//
//  //Sum the current values in the buffer
//  for (i = 0; i < BUFF_SIZE; i++) {
//    sum = sum + Read_Circ_Buff (&buffer);
//  }
//  //Calculate the average
//  avg = (sum / BUFF_SIZE);
//  return avg;
//}
  














