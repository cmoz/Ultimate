int sensorPin = 1;
int ledPin = 2;

void setup() {
pinMode(sensorPin, INPUT);
pinMode(ledPin, OUTPUT);
}

void loop() {
int read = digitalRead(sensorPin);

if (read == LOW) {
digitalWrite(ledPin, HIGH);
delay(500);
}

else {
digitalWrite(ledPin, LOW);
}
} 