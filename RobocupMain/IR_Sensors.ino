#include <SharpIR.h>


//***********************************************************************************************
// Initialisation functions
//***********************************************************************************************

void initVcc()
{
  // turn Vcc on (5V)
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);
}
void initSerial()
{
  // initialize serial communications at set baudrate:
  Serial.begin(BAUDRATE);
}
  
void setupIR()
{

  pinMode(IRmed_L_Pin, INPUT);
  pinMode(IRmed_R_Pin, INPUT);
  pinMode(IRlong_L_Pin, INPUT);
  pinMode(IRlong_R_Pin, INPUT);

}

//***********************************************************************************************
//
//***********************************************************************************************
int readIRMed(int IR_Pin)
{
  SharpIR sharp(IR_Pin, 25, 93, 1080);
  int IR_cm;

  // read the analog in value and convert to cm:
  int IR_volt = map(analogRead(IR_Pin), 0, 1023, 0, 5000);
  //int IR_cm = 4800/(IR_volt - 20)*100;
  //int IR_cm = (21.61 / (IR_volt - 0.1696)) * 1000;
  //if (IR_volt > 2000) IR_cm = -1.0;        // out of range
  
  
  //Check to see if sensor readin gis within valid range
  if (IR_volt>400 && IR_volt<2700){
    IR_cm = sharp.distance();
  }
  else IR_cm = -1;      //Set distance to '-1' if sensor is out of range
  
  return IR_cm;
}

int readIRLong(int IR_Pin)
{
  SharpIR sharp(IR_Pin, 25, 93, 20150);
  
  //read the analog in value and convert to cm:
  //int IR_volt = map(analogRead(IR_Pin), 0, 1023, 0, 5000);
  //int IR_cm = 6786/(analogRead(IR_Pin)-3) - 4;  //((21.61 / (IR_volt - 0.1696)) * 1000;
  // if (IR_volt > 2000) IR_cm = -1.0;        // out of range
  
  int IR_cm=sharp.distance();  
  return IR_cm;
}

