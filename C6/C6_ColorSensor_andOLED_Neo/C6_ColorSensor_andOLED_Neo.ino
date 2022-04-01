#include <Wire.h>                  //include Wire.h to be able to communicate through I2C on Arduino board
#include "Adafruit_TCS34725.h"     //Colour sensor library
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_NeoPixel.h"

//Create colour sensor object declaration, to see effects of different integration time and gain
//settings, check the datatsheet of the Adafruit TCS34725.  
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define LED_PIN    10
#define LED_COUNT 25

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  //Start-up colour sensor
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  
}

void loop() {

  uint16_t clear, red, green, blue; 

  //Collect raw data from integrated circuit using interrupts
  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; 
  r /= sum;
  g = green; 
  g /= sum;
  b = blue; 
  b /= sum;
  r *= 256; g *= 256; b *= 256;

  Serial.print("HEX: \t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);

  Serial.print("\t \t RGB: \t");
  Serial.print((int)r ); 
  Serial.print(" "); 
  Serial.print((int)g);
  Serial.print(" ");  
  Serial.println((int)b );
  Serial.println();

  colorWipe(strip.Color(r, g, b), 50); 

  oled.clearDisplay();          // clear displa
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(2, 10);        // position to display
  oled.println("HEX:");
  oled.setCursor(50, 10);        // position to display
  oled.println((int)r, HEX); 
  oled.setCursor(74, 10);        // position to display
  oled.println((int)g, HEX); 
  oled.setCursor(98, 10);        // position to display
  oled.println((int)b, HEX);     // text to display
  oled.display();                // show on OLED
  
  delay(5000);

}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
