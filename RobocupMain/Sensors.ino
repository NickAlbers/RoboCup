#include <SharpIR.h>
//***********************************************************************************************
// Initialisation functions
//***********************************************************************************************

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

void setupUltra() 
{  
  pinMode(Ultra_L_trigPin, OUTPUT);            //Setup ultrasound pins
  pinMode(Ultra_L_echoPin, INPUT);
  pinMode(Ultra_R_trigPin, OUTPUT);
  pinMode(Ultra_R_echoPin, INPUT);
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
//  if (IR_volt>400 && IR_volt<2700){
//    IR_cm = sharp.distance();
//  }
//  else IR_cm = -1;      //Set distance to '-1' if sensor is out of range
  if (IR_volt <400){
    IR_cm = 80;
  }
  else if (IR_volt > 2700){
    IR_cm = 0;
  }
  else  IR_cm = sharp.distance();
  
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


 
//***********************************************************************************************
//Functions for ultrasound
//***********************************************************************************************

long readUltra(int trigPin, int echoPin)
{
  long duration, cm;
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  return cm;
}

 
long microsecondsToCentimeters(long microseconds)
{
  //return microseconds / 29 / 2;
  return (microseconds / 82);
} 

