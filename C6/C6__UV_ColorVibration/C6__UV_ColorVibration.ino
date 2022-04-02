#include <Adafruit_CircuitPlayground.h>
#include "Adafruit_SI1145.h"

Adafruit_SI1145 uv = Adafruit_SI1145();

float UVthresholdIndoors = 2;
int vibePin = 1;

void setup() {
Serial.begin(9600);
CircuitPlayground.begin();
Serial.println("Adafruit SI1145 test");

if (! uv.begin()) {
Serial.println("Didn't find Si1145");
while (1);
}
Serial.println("OK!");
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
  neoColor(0,255,100);
  
  } else 

  if(uv.readUV()>=690 && uv.readUV()<1379)
  {
  Serial.println("Moderate");
  CircuitPlayground.playTone(345, 200);
  neoColor(255,191,0);
  digitalWrite(vibePin, HIGH);
  } else 

   if(uv.readUV()>=1380 && uv.readUV()<1839)
  {
  Serial.println("High");
  CircuitPlayground.playTone(445, 200);
  neoColor(255,0,255);
  digitalWrite(vibePin, HIGH);
  } else

  if(uv.readUV()>=1839 && uv.readUV()<2529)
  {
  Serial.println("Very High");
  CircuitPlayground.playTone(655, 400);
  neoColor(244,30,30);
  digitalWrite(vibePin, HIGH);
  }

  if(uv.readUV()>=2530 && uv.readUV()<2760)
  {
  Serial.println("Extreme high");
  CircuitPlayground.playTone(755, 600);
  neoColor(255,0,0);
  digitalWrite(vibePin, HIGH);
  }

delay(1000);
} 

void neoColor(int r, int g,int b){
  for (int neoPin = 0; neoPin <=10; neoPin++){
  CircuitPlayground.setPixelColor(neoPin,r,g,b);
  delay(20);
  }
  
}
