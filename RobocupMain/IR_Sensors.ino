const int IR1_Pin = A0;
const int IR2_Pin = A1;
const int irTimeDelay = 100;

int IR2_volt = 0;
int IR2_cm = 0;
//***********************************************************************************************
//
//***********************************************************************************************
void setupIRMed()
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  pinMode(IR1_Pin, INPUT);
  pinMode(IR2_Pin, INPUT);
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);
}

//***********************************************************************************************
//
//***********************************************************************************************
int readIRMed()
{
  int IR_volt = 0;
  int IR_cm = 0;
  
  // read the analog in value and convert to cm:
  IR_volt = map(analogRead(IR1_Pin), 0, 1023, 0, 5000);
  IR_cm = (21.61 / (IR_volt - 0.1696)) * 1000;
  if (IR_volt > 2000) IR_cm = -1.0;        // out of range
  
  Serial.println(IR_cm);
  
  return IR_cm;
}

