const int IR1_Pin = A0;
const int IR2_Pin = A1;

int IR1_volt = 0;
int IR2_volt = 0;
int IR1_cm = 0;
int IR2_cm = 0;
//***********************************************************************************************
//
//***********************************************************************************************
void setupIR() 
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
void readIR() 
{
  // read the analog in value:
  IR1_volt = analogRead(IR1_Pin);
  IR1_volt =map(IR1_volt, 0, 1023, 0, 5000);
  IR1_cm =(21.61/(IR1_volt-0.1696))*1000;
  if (IR1_volt > 2000) IR1_cm = -1.0;        // out of range   
  
  IR2_volt = analogRead(IR2_Pin);
  IR2_volt =map(IR2_volt, 0, 1023, 0, 5000);
//  IR2_cm = 60.495 * pow(IR2_volt,-1.1904);     
  IR2_cm =(9.462/(IR2_volt-0.01692))*1000;
  if (IR2_volt > 20000) IR2_cm = -1.0;        // out of range  
 
  // print the results to the serial monitor:
  Serial.print("\n" );
  Serial.print(IR1_cm);
  Serial.print("      ");
  Serial.print(IR2_cm);

  delay(100);
}
