#include <SharpIR.h>

//***********************************************************************************************
// Function:
//This function reads all sensors and stores them in the robot struct
//***********************************************************************************************

/* Function: Sensors_UpdateAll
 *  This function reads all sensors and stores them in the robot struct
 */
 
void Sensors_UpdateAll(_Robot *Bagger)
{
  //int tick = millis();
   //Serial.println("Update Sensors");
  //Bagger->IRlong_L = IR_ReadMed(IRlong_L_Pin);
  //Bagger->IRlong_R = IR_ReadMed(IRlong_R_Pin);
  
  
  Bagger->IRmed_L = IR_ReadMed(IRmed_L_Pin);
  Bagger->IRmed_R = IR_ReadMed(IRmed_R_Pin);
  
  
  Bagger->Ultra_L = Ultra_L.ping_cm();
  Bagger->Ultra_R = Ultra_R.ping_cm();
  Bagger->Ultra_LT = Ultra_LT.ping_cm();
  Bagger->Ultra_RT = Ultra_RT.ping_cm();

  if(Bagger->Ultra_L==0)Bagger->Ultra_L=MAX_ULTRA;
  if(Bagger->Ultra_R==0)Bagger->Ultra_R=MAX_ULTRA;
  if(Bagger->Ultra_LT==0)Bagger->Ultra_LT=MAX_ULTRA;
  if(Bagger->Ultra_RT==0)Bagger->Ultra_RT=MAX_ULTRA;
//  Serial.print(Bagger->Ultra_L);
//  Serial.print("\t | \t");
//  Serial.print(Bagger->Ultra_LT);
//  Serial.print("\t || \t");
//  Serial.print(Bagger->Ultra_R);
//  Serial.print("\t | \t");
//  Serial.println(Bagger->Ultra_RT);
  //int tock = millis();
  //Serial.println(tock-tick);
}
  
//***********************************************************************************************
// INFRARED SENSORS
//***********************************************************************************************
void setupIR()
{
  pinMode(IRmed_L_Pin, INPUT);
  pinMode(IRmed_R_Pin, INPUT);
  pinMode(IRlong_L_Pin, INPUT);
  pinMode(IRlong_R_Pin, INPUT);
}

int IR_ReadMed(int IR_Pin)
{
  SharpIR sharp(IR_Pin, 25, 93, 1080);
  int IR_cm;

  // read the analog in value and convert to cm:
  int IR_volt = map(analogRead(IR_Pin), 0, 1023, 0, 5000);
  if (IR_volt <400){
    IR_cm = 80;
  }
  else if (IR_volt > 2700){
    IR_cm = 0;
  }
  else  IR_cm = sharp.distance();
  
  return IR_cm;
}

int IR_ReadLong(int IR_Pin)
{
  SharpIR sharp(IR_Pin, 25, 93, 20150);
  int IR_cm=sharp.distance();  
  return IR_cm;
}

//***********************************************************************************************
// ULTRASONIC SENSOR
//***********************************************************************************************

void setupUltra() 
{  
  pinMode(Ultra_L_trigPin, OUTPUT);            //Setup ultrasound pins
  pinMode(Ultra_L_echoPin, INPUT);
  pinMode(Ultra_R_trigPin, OUTPUT);
  pinMode(Ultra_R_echoPin, INPUT);
}

long Ultra_Read(int trigPin, int echoPin)
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
  duration = pulseIn(echoPin, HIGH, PULSE_TIMEOUT);
 
  // convert the time into a distance
  cm = Ultra_ConvertMicrosecondsToCentimeters(duration);
  return cm;
}

 
long Ultra_ConvertMicrosecondsToCentimeters(long microseconds)
{
  //return microseconds / 29 / 2;
  return (microseconds / 82);
} 

//***********************************************************************************************
// COLOUR SENSOR
//***********************************************************************************************

#include <Wire.h>
#include "Adafruit_TCS34725.h"

//Blue Home is:n 649: R:202 G:224 B:221
//Green Home is:n 649: R:202 G:224 B:100

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setupColourSensor()
{
  Serial.println("Color View Test!");

  if (tcs.begin())
  {
    Serial.println("Found sensor");
  } else
  {
    Serial.println("No TCS34725 found ... check your connections");
    //while (1); // halt!
  }
}

void Colour_Read(_Robot *Bagger)
{
  Serial.println("Reading Colour Sensor");
  Serial.println(" ");

  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read //Commenting this out may cause errors

  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true);  // turn off LED

//  Serial.print("C:\t"); Serial.print(clear);
//  Serial.print("\tR:\t"); Serial.print(red);
//  Serial.print("\tG:\t"); Serial.print(green);
//  Serial.print("\tB:\t"); Serial.print(blue);

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
//  Serial.print("\t");
//  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
//  Serial.println();

  //Guess the current colour
  //  if ((red > 150 && red < 250) && (green > 150 && green < 250) && (blue > 150 && blue < 250)) {
  //    Serial.println("The colour is blue");
  //    UpdateLED(0,0,256);
  //    return;
  //  }
  //  if ((red > 150 && red < 250) && (green > 100) && (blue > 50 && blue < 150)) {
  //    Serial.println("The colour is green");
  //        UpdateLED(0,256,0);
  //    return;
  //  }
  //  else {
  //    Serial.println("The colour is black");

  if (((green / blue) > 1.0) && (green > 100))  {
    Serial.println("The colour is blue");
    LED_Update(0, 0, 255);
    return;
  }
  else if (((blue / red) > 1.75) && (blue > green) && (blue > 150)) {
    Serial.println("The colour is green");
    LED_Update(0, 255, 0);
    return;
  }
  else {
    Serial.println("No colour detected");
  }  
  
//  else if (((red / blue) > 1.5) && (red > 150)) {
//    Serial.println("The colour is red");
//    UpdateLED(255, 0, 0);
//    return;
//  }
  //  if ((green > red) && (green > blue));
  //  {
  //    Serial.println("The colour is green");
  //    UpdateLED(0, 255, 0);
  //    return;
  //  }
  //  if ((blue > red) && (blue > green));
  //  {
  //    Serial.println("The colour is blue");
  //    UpdateLED(0, 0, 255);
  //    return;
  //  }
  //  Serial.println("No colour detected");
  //  UpdateLED(0, 0, 0);
}

//***********************************************************************************************
// WEIGHT
//***********************************************************************************************

void setupWeight() 
{
  scale.setOffset(0);
  scale.setScale(1000); //?
}
 
void Weight_GetWeight() 
{
  Serial.print(scale.getGram(), 1);    //Get force and print answer
  Serial.println(" g");
}

