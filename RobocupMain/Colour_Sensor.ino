#include <Wire.h>
#include "Adafruit_TCS34725.h"

//Blue Home is:n 649: R:202 G:224 B:221
//Green Home is:n 649: R:202 G:224 B:100

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setupColourSensor()
{
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board

  Serial.begin(9600);
  Serial.println("Color View Test!");

  if (tcs.begin())
  {
    Serial.println("Found sensor");
  } else
  {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
}


void readColourSensor()
{
  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true);  // turn off LED

  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();

  //Guess the current colour
  if ((red > 150 && red < 250) && (green > 150 && green < 250) && (blue > 150 && blue < 250)) {
    Serial.println("The colour is blue");
    return;
  }
  if ((red > 150 && red < 250) && (green > 100 && green < 300) && (blue > 50 && blue < 150)) {
    Serial.println("The colour is green");
    return;
  }
  else {
    Serial.println("The colour is black");
  }
}

