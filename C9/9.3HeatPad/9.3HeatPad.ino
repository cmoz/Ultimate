/******************************************************************************


*****************************************************************************/

#include <Adafruit_NeoPixel.h>

int heatPin = 8;
int neoLine = A2;
int numNeos = 8;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(numNeos, neoLine, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(heatPin, OUTPUT);
  digitalWrite(heatPin, HIGH);
  strip.begin();
  strip.setBrightness(45);
  strip.show();

}

void loop() {
  // put your main code here, to run repeatedly:
  rainbowCycle(20);

}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
strip.setBrightness(45);
  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
