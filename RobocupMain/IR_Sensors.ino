#include <SharpIR.h>

//SharpIR sharp(IRleft_Pin, 25, 93, 1080);

//***********************************************************************************************
//
//***********************************************************************************************

void initVcc()
{
  // turn Vcc on (5V)
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);
}

void setupIRMed()
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  pinMode(IRmed_L_Pin, INPUT);
  pinMode(IRmed_R_Pin, INPUT);
  pinMode(IRlong_L_Pin, INPUT);
  pinMode(IRmed_R_Pin, INPUT);

}

//***********************************************************************************************
//
//***********************************************************************************************
int readIRMed(int IR_Pin)
{
  int IR_volt = 0;
  int IR_cm = 0;
  
  // read the analog in value and convert to cm:
  IR_volt = map(analogRead(IR_Pin), 0, 1023, 0, 5000);
  //IR_cm = 4800/(IR_volt - 20)*100;
  IR_cm = (21.61 / (IR_volt - 0.1696)) * 1000;
  if (IR_volt > 2000) IR_cm = -1.0;        // out of range
  
//  int dis=sharp.distance();
// Serial.print(IR_volt);
// Serial.print("    ");
// Serial.println(IR_cm);
  //Serial.println(dis);  
  return IR_cm;
}

int readIRLong(int IR_Pin)
//conversion to cm does not work yet...
{
  SharpIR sharp(IR_Pin, 25, 93, 20150);
  //  int IR_volt = 0;
  int IR_cm = 0;
  
  // read the analog in value and convert to cm:
  //IR_volt = map(analogRead(IR_Pin), 0, 1023, 0, 5000);
  //IR_cm = 6786/(analogRead(IR_Pin)-3) - 4;  //((21.61 / (IR_volt - 0.1696)) * 1000;
  // if (IR_volt > 2000) IR_cm = -1.0;        // out of range
  
  int dis=sharp.distance();
  //  Serial.println(dis);
  
  return IR_cm;
}

