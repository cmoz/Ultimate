#include <Adafruit_CircuitPlayground.h>

float X, Y, Z;
#define MOVE_THRESHOLD 3 //To 10, lower the number more sensitive

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  CircuitPlayground.clearPixels();
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
 
  // Get the magnitude (length) of the 3 axis vector
  // http://en.wikipedia.org/wiki/Euclidean_vector#Length
  double storedVector = X*X;
  storedVector += Y*Y;
  storedVector += Z*Z;
  storedVector = sqrt(storedVector);
  Serial.print("Len: "); Serial.println(storedVector);
  
  // wait a bit
  delay(100);
  
  // get new data
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
  double newVector = X*X;
  newVector += Y*Y;
  newVector += Z*Z;
  newVector = sqrt(newVector);
  Serial.print("New Len: "); Serial.println(newVector);
  
  // movement 
  if (abs(10*newVector - 10*storedVector) > MOVE_THRESHOLD) {

    for (int x=0; x<10; x++){

    int randomValR = random(255); 
    int randomValG = random(255);
    int randomValB = random(255);
    int randomNeoPos = random(10);
    CircuitPlayground.setPixelColor(randomNeoPos, 
                                    randomValR,  randomValG,   randomValB);

delay(100);

    x = randomNeoPos; 

    }
  }
  
  delay(100);
}
