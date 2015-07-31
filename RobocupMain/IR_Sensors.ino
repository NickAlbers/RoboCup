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
<<<<<<< HEAD
  static long irNextTime = 0;
  if (millis() < irNextTime)
  {
    return;
  }
  //    return;
  // read the analog in value:
  IR1_volt = analogRead(IR1_Pin);
  IR1_volt = map(IR1_volt, 0, 1023, 0, 5000);
  IR1_cm = (21.61 / (IR1_volt - 0.1696)) * 1000;
  if (IR1_volt > 2000) IR1_cm = -1.0;        // out of range

  IR2_volt = analogRead(IR2_Pin);
  IR2_volt = map(IR2_volt, 0, 1023, 0, 5000);
  //  IR2_cm = 60.495 * pow(IR2_volt,-1.1904);
  IR2_cm = (9.462 / (IR2_volt - 0.01692)) * 1000;
  if (IR2_volt > 20000) IR2_cm = -1.0;        // out of range

  // print the results to the serial monitor:
  Serial.println(IR1_cm);
  Serial.println(IR2_cm);
=======
  int IR_volt = 0;
  int IR_cm = 0;
  
  // read the analog in value and convert to cm:
  IR_volt = map(analogRead(IR1_Pin), 0, 1023, 0, 5000);
  IR_cm = (21.61 / (IR_volt - 0.1696)) * 1000;
  if (IR_volt > 2000) IR_cm = -1.0;        // out of range
  
  Serial.print("\n" );
  Serial.print(IR_cm);
>>>>>>> origin/master
  
  return IR_cm;
}
  
//  static long irNextTime = 0;
//  if (millis() < irNextTime)
//  {
//    return;
//  }
//  
//
//  IR2_volt = analogRead(IR2_Pin);
//  IR2_volt = map(IR2_volt, 0, 1023, 0, 5000);
//  //  IR2_cm = 60.495 * pow(IR2_volt,-1.1904);
//  IR2_cm = (9.462 / (IR2_volt - 0.01692)) * 1000;
//  if (IR2_volt > 20000) IR2_cm = -1.0;        // out of range
//
//  // print the results to the serial monitor:
//  Serial.print("\n" );
//  Serial.print(IR1_cm);
//  Serial.print("      ");
//  Serial.print(IR2_cm);
//  
//  irNextTime = millis() + irTimeDelay;
//}
