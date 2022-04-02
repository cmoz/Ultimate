/* 
 *  2022 @cmoz
 *  
 *  This code is for a circuit created for the Circuit Playground boards
 *  It uses a Circuit Playground Classic, sewable UV sensor, battery, 
 *  battery charger, and vibration motor, onboard sound and NeoPixels
 *  
 *  Program:   Wearable UV sensor on a cap to detect UV rating outside
 *             Circuit: UV sensor (SDA/SCL pins)
 *             vibration motor (pin 1)
 *             
 *             If UV rating is higher than an indoor rating:
 *             Hat will vibrate, NeoPixels will change color, sound will happen
 *             
 */

#include <Adafruit_CircuitPlayground.h>
#include "Adafruit_SI1145.h"

Adafruit_SI1145 uv = Adafruit_SI1145();

float UVthresholdIndoors = 2;
int vibePin = 1;

void setup() {
Serial.begin(9600);
CircuitPlayground.begin();

  if (! uv.begin()) {
  Serial.println("Didn't find Si1145");
  while (1);
  }
  
 pinMode(vibePin, OUTPUT);

}

void loop() {
  digitalWrite(vibePin, LOW);
  Serial.println("===================");
  
  float UVindex = uv.readUV();
  Serial.print("UV: "); Serial.println(UVindex);
  Serial.println(uv.readUV());

    if(uv.readUV()>= UVthresholdIndoors && uv.readUV()<689 )
    {
      Serial.println("LOW");
      neoColor(0,255,100); //blue color
      digitalWrite(vibePin, LOW); // no vibration if we are indoors or low reading
    } else 
  
    if(uv.readUV()>=690 && uv.readUV()<1379) 
    {
      Serial.println("Moderate");
      CircuitPlayground.playTone(345, 200);
      neoColor(255,191,0); //yellow color
      vibrationWarn(100, 5);
    } else 
  
     if(uv.readUV()>=1380  && uv.readUV()<1839)
    {
      Serial.println("High");
      CircuitPlayground.playTone(445, 200);
      neoColor(255,0,255); // purple color
      vibrationWarn(200, 10);
    } else
  
    if(uv.readUV()>=1839 && uv.readUV()<2529)
    {
      Serial.println("Very High");
      CircuitPlayground.playTone(655, 400);
      neoColor(244,30,30); // red color
      vibrationWarn(300, 15);
    }
  
    if(uv.readUV()>=2530 && uv.readUV()<2760)
    {
      Serial.println("Extreme high");
      CircuitPlayground.playTone(755, 600);
      neoColor(255,0,0); //full red color
      vibrationWarn(400, 20);
    }

  delay(1000);
} 

// +++ Functions for the code

// Function to change the colors of NeoPixels
void neoColor(int r, int g,int b){
  for (int neoPin = 0; neoPin <=10; neoPin++){
  CircuitPlayground.setPixelColor(neoPin,r,g,b);
  delay(20);
  }
}

// Function for the vibration to be different depending on the danger 
void vibrationWarn(int pulseDuration, int amount){
  for (int loops = 0; loops <= amount; loops++){
      digitalWrite(vibePin, HIGH);
      delay(pulseDuration);
      digitalWrite(vibePin, LOW);
      delay(pulseDuration);
  }
}
