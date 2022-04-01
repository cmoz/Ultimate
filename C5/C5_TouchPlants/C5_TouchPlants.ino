#include "ADCTouch.h"

#include <Servo.h>
Servo myservo;

int ref0, ref1;
int touchPin1 = A7;
int touchPin2 = A9;

int val0constrained = 0;

int val0high = 400;
int val0low = 0;

int threshold = 10;
int pos = 0;

void setup()
{
  Serial.begin(9600);

  myservo.attach(12);

  ref0 = ADCTouch.read(touchPin1, 500); 
  ref1 = ADCTouch.read(touchPin2, 500); 
}

void loop()
{
  int value0 = ADCTouch.read(touchPin1);
  int value1 = ADCTouch.read(touchPin2); 

  value0 -= ref0; 
  value1 -= ref1;

  Serial.print(value0 > threshold);
  Serial.print("\t");

  Serial.print(value1 > threshold);
  Serial.print("\t\t");

  Serial.print(value0);
  Serial.print("\t");

  Serial.println(value1);
 
 myservo.write(0);
  if (value0 > threshold) {

    myservo.write(180);
  }

 delay(100);
}
