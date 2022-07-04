#include <Adafruit_NeoPixel.h>

int neoLine = 1;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, neoLine, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(45);
  strip.show();
  
//  add the rainbow function here
//  rainbowEffect(1, 3); 
//  strip.fill((0,0,0), 0, 10);
//  strip.show();
  
  delay(300);
  Serial.println("set up ready"); 
}

void loop() {

}

// modify this function to take 2 variable

void rainbowEffect(uint8_t wait) {
  uint16_t x, y;
strip.setBrightness(45);
  for (y = 0; y < 256 * 5; y++) { // 5 cycles of all colors on wheel
    for (x = 0; x < strip.numPixels(); x++) {
      strip.setPixelColor(x, Wheel(((x * 256 / strip.numPixels()) + y) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte StripPos) {
  StripPos = 255 - StripPos;
  if (StripPos < 85) {
    return strip.Color(255 - StripPos * 3, 0, StripPos * 3);
  }
  if (StripPos < 170) {
    StripPos -= 85;
    return strip.Color(0, StripPos * 3, 255 - StripPos * 3);
  }
  StripPos -= 170;
  return strip.Color(StripPos * 3, 255 - StripPos * 3, 0);
}
