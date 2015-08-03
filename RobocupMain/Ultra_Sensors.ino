//***********************************************************************************************
//Setup
//***********************************************************************************************
void setup_Ultra() 
{  
  pinMode(Ultratrig_L_Pin, OUTPUT);            //Setup ultrasound pins
  pinMode(Ultraecho_L_Pin, INPUT);
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
  Serial.print(cm);
  Serial.println();
  return cm;
}

 
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
} 
