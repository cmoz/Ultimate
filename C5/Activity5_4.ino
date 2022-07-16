#define sensorPin 7
int ledPin = 2;

unsigned long lastEvent = 0;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorData = digitalRead(sensorPin);

  if (sensorData == LOW) {
    if (millis() - lastEvent > 25) {
      Serial.println("Clap detected!");
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
    }
    lastEvent = millis();
  }
}
