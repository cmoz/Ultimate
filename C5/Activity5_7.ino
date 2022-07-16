#include "ADCTouch.h"
#include <Servo.h>

Servo myservo;

int ref0;
int touchPin1 = A7;
int val0constrained = 0;
int val0high = 350;
int val0low = 0;
int threshold = 10;
int pos = 0;

void setup()
{
  Serial.begin(9600);
  myservo.attach(12);
  ref0 = ADCTouch.read(touchPin1, 500);
}

void loop()
{
  int value0 = ADCTouch.read(touchPin1);
  value0 -= ref0;
  Serial.println(value0);

  myservo.write(0);
  if (value0 > threshold) {
    myservo.write(180);
  }
  delay(100);
}
