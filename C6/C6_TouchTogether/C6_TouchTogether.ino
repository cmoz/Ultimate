#include <Adafruit_CircuitPlayground.h>

uint8_t pixeln = 0;
int capsense[10];
int vibePin = 3;

void setup() {
  CircuitPlayground.begin();
  
   for(int i=0; i< CircuitPlayground.strip.numPixels(); i++) {
    CircuitPlayground.setPixelColor(i, (  0,  0, 255));
    CircuitPlayground.strip.show();
    CircuitPlayground.playTone(984, 30);
    delay(40);
  }
  delay(1000);
  pinMode(vibePin, OUTPUT);
  CircuitPlayground.clearPixels();
}


void loop() {
  digitalWrite(vibePin, LOW);
  
  //capsense[0] = CircuitPlayground.readCap(3); if using vibration we cant sense on this pin
  capsense[1] = CircuitPlayground.readCap(2);
  capsense[2] = CircuitPlayground.readCap(0);
  capsense[3] = CircuitPlayground.readCap(1);
  capsense[4] = CircuitPlayground.readCap(12);
  capsense[5] = CircuitPlayground.readCap(6);
  capsense[6] = CircuitPlayground.readCap(9);
  capsense[7] = CircuitPlayground.readCap(10);

  int frequency = 0;
  
 if  (capsense[0] > 100) {
    frequency = 523;
    for (int x = 0; x < 10; x++){
    CircuitPlayground.setPixelColor(x,75,0,130);
    }
    vibration();
  } else if  (capsense[1] > 100) {
    frequency = 587;
    for (int x = 0; x < 10; x++){
    CircuitPlayground.setPixelColor(x, 0,0,255);
    }
  } else if  (capsense[2] > 100) {
    frequency = 659;
    for (int x = 3; x < 10; x++){
    CircuitPlayground.setPixelColor(x, 138,43,226);
    }
    vibration();
  } else if  (capsense[3] > 100) {
    frequency = 698;
    for (int x = 4; x < 10; x++){
    CircuitPlayground.setPixelColor(x, 216,191,216);
    }
    vibration();
  } else if  (capsense[4] > 100) {
    frequency = 784;
    for (int x = 5; x < 10; x++){
    CircuitPlayground.setPixelColor(x, 238,130,238);
    }
    vibration();
  } else if  (capsense[5] > 100) {
    frequency = 880;
    for (int x = 6; x < 10; x++){
    CircuitPlayground.setPixelColor(x, 0,191,255);
    }
    vibration();
  } else if  (capsense[6] > 100) {
    frequency = 988;
    for (int x = 8; x < 10; x++){
    CircuitPlayground.setPixelColor(x, 199,21,133);
    }
    vibration();
  } else if  (capsense[7] > 100) {
    frequency = 1046;
    for (int x = 9; x < 10; x++){
    CircuitPlayground.setPixelColor(x, 138,43,226);
    }
    vibration();
  }
  delay(10);
  CircuitPlayground.clearPixels();
  CircuitPlayground.playTone(frequency, 200);
}

void vibration(){
  digitalWrite(vibePin, HIGH);
  delay(200);
  digitalWrite(vibePin, LOW);
}
