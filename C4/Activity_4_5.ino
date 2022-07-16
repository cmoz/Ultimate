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
