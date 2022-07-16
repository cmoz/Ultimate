/*
@cmoz

There is a new function in the loop() code block. We use map() to map values 0-1023 to 0-255 of pulse width modulation (PWM). This re-maps a number from one range into a different range. Here we are mapping to the max value, 255 that we can use with the LED, which we want to light from the values.
Test your flex sensor and find out what your values are. I’ve remapped mine to hold the values 848 to 1015, so I’ve modified that line of code to read:

flexValue = map(flexValue, 848, 1015, 0, 255);

You will change these values because your flex sensor is different from mine.
*/

int ledPin = 9; 
int flexPin = 10;
int flexValue;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(flexPin, INPUT);
  Serial.begin(9600);       
}

void loop(){
  flexValue = analogRead(flexPin);
  Serial.println(flexValue); 
  flexValue = map(flexValue, 848, 1015, 0, 255);
  analogWrite(ledPin, flexValue);
  delay(100);                          
}
