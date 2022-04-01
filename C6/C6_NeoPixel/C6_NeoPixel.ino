#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    10

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60

// Declare NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  // Fill along the length of the strip in various colors..

for(int i=0; i<strip.numPixels(); i++) {   // For each pixel in strip...
    strip.setPixelColor(i, (0, 0, 220));   //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(1000);                           //  Pause for a moment
  }
  
}
