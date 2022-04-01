#define MYRESISTOR 10000    
#define STRETCHPIN A0 
 
void setup(void) {
  Serial.begin(9600);
}


void loop(void) {
  float reading;
 
  reading = analogRead(STRETCHPIN);
 
  reading = (1023 / reading)  - 1;  
  reading = MYRESISTOR / reading; 
  Serial.print("Resistance "); 
  Serial.println(reading);

  if (reading > 4700) {
  Serial.println(" No stretch");
    } else if (reading < 4000) {
    Serial.println(" stretch");
    } else {
    Serial.println(" relaxed");
  }
 
  delay(200);
}
