
static long nextRun = 0;
//***********************************************************************************************
//Function allowing the robot to steer autonomously
//***********************************************************************************************
void autonomousDrive()
{
  static RobotState driveState = DRIVING;

  static int turnDir = 1;

  //Can I turn yet? Check for the run time and whether or not evasive tactics is enabled
  if ((millis() < nextRun) && (driveState != EVASIVETACTICS)) {
    return;
  }

  switch (driveState) {
    case DRIVING:
      Serial.println("Driving");
      //Generate a time to drive for, and set the next state to be turning
      nextRun = millis() + random(500, 6000);
      driveForward();
      driveState = TURNING; // Set the next run to be driving forwards
      break;

    case TURNING:
      Serial.println("Turning");
      //Generate a time to turn for
      turnDir = random(0, 2); //Random function chooses between min and max-1
      nextRun = millis() + random(1000, 3000);
      driveTurn(turnDir);
      driveState = DRIVING; //Set the next run to be a drive command
      break;
  }
}

//***********************************************************************************************
// Read the medium range IR sensors, and execute collision avoidance code if a collision is
// imminent, return true if an object is within "safeDistance" centimeters
//***********************************************************************************************
void collisionDetect()
{
  static int collisionDist1 = avg_Circ_Buff(irMedLeftBuff);
  static int collisionDist2 = avg_Circ_Buff(irMedRightBuff);
  Serial.println(collisionDist1);
  Serial.println(collisionDist2);
  
  if ((collisionDist2  <= SAFEDISTANCE) || (collisionDist2  <= SAFEDISTANCE)) {
    Serial.println("COLLISION DETECTED");
    evasiveManeouvers();
    return;
  }
  else {
    return;
  }
}

//***********************************************************************************************
// Scan for packages and inititiate relevant code
//***********************************************************************************************
void packageDetect()
{
  return;
}

//***********************************************************************************************
// Check the collision sensors, then execute avoidance maneouveres THESE VALUES REQUIRE TWEAKING
// THIS FUNCTION IS BLOCKING
//***********************************************************************************************

void evasiveManeouvers()
{
  static long nextRun = 0;
  Serial.println("EVASIVE MANOUEVERS");
  //Read the collision detection sensors and guess the shortest path out of the collision
  int leftSensor = avg_Circ_Buff(irMedLeftBuff);
  int rightSensor = avg_Circ_Buff(irMedRightBuff);

  int collisionDirection = (leftSensor - rightSensor); //Work out fastest turn direction to avoid collision

  if (collisionDirection < 0) //Right sensor reads further away than left sensor
  {
    driveTurn(1);
    nextRun = millis() + random(500, 1000);
    Serial.println("RIGHT");
  }
  else if (collisionDirection >= 0) //Left sensor reads further away than right sensor
  {
    driveTurn(0);
    nextRun = millis() + random(500, 1000);
    Serial.println("LEFT");
  }
  driveState = DRIVING; //The next run should be to drive forwards
}


//***********************************************************************************************
// This function reads all sensors and writes them into an averaging circular buffer
//***********************************************************************************************

void updateSensors()
{
  readSensor(readIRMed(A0), irMedLeftBuff);
  readSensor(readIRMed(A1), irMedRightBuff);
}

void readSensor(int sensor, circBuf_t buffer)
{
  buffer.data[irMedLeftBuff.windex] = (int) sensor;
  buffer.windex ++; // Incremeant the write pointer
  if (buffer.windex >= buffer.size) // Wrap the buffer if its reached the end
    buffer.windex = 0;
}

int avg_Circ_Buff(circBuf_t buffer)
{
  //Average the values in the buffer
  int avg;
  int sum;
  unsigned int i;

  //Sum the current values in the buffer
  for (i = 0; i < BUFF_SIZE; i++) {
    sum = sum + Read_Circ_Buff (&buffer);
  }
  //Calculate the average
  avg = (sum / BUFF_SIZE);
  return avg;
}
  














