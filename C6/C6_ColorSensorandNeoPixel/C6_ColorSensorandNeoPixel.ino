#include <Wire.h>                  //include Wire.h to be able to communicate through I2C on Arduino board
#include "Adafruit_TCS34725.h"     //Colour sensor library

//Create colour sensor object declaration, to see effects of different integration time and gain
//settings, check the datatsheet of the Adafruit TCS34725.  
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  Serial.println("Color View Test!");

  //Start-up colour sensor
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
}


void loop() {

  uint16_t clear, red, green, blue; 

  //Collect raw data from integrated circuit using interrupts
  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; 
  r /= sum;
  g = green; 
  g /= sum;
  b = blue; 
  b /= sum;
  r *= 256; g *= 256; b *= 256;

  Serial.print("HEX: \t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);

  Serial.print("\t \t RGB: \t");
  Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );
  Serial.println();
}
