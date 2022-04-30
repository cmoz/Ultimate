/* 
 *  Works on Flora and Circuit Playground boards. Will need to modify for the 
 *  NeoPixel strip is all, depending on the board.s
 *  
 *  OLED using I2C
 *  KEYBOARD USB to input the HEX code into where their curcor is
 *  Uses button / conductive fabric to press to copy the code to text file
 *  
 *  NEOs on PIN 10
 *  BUTTON on PIN 12 
 *  
 */

// ****EDIT THIS FIRST*** KEEP the name of the board you are using: 
// NON_CP (for any boards that are not a Circuit Playground based board, in our example we use a Flora) or 
// CIRCUIT_PLAYGROUND (for any Circuit Playground boards)
//
// This is because the NeoPixels which work a little
// differently when you have a Circuit Playground board.
// This will remove or include the Circuit Playground specific code.
 
#define NON_CP

// =======================================================================================

#include "Keyboard.h"
#include <Wire.h>                  //include Wire.h to be able to communicate through I2C on Arduino board

#ifdef CIRCUIT_PLAYGROUND
#include <Adafruit_CircuitPlayground.h>
#endif

#include "Adafruit_TCS34725.h"     //Colour sensor library
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#include "Adafruit_NeoPixel.h" 

//Create colour sensor object declaration, to see effects of different integration time and gain
//settings, check the datatsheet of the Adafruit TCS34725.
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define LED_PIN    10   // Change to the pin your neopixels are on
#define LED_COUNT  25   // change to the number of NeoPixels you are using

int pushButton = 12;
int previousButtonState = HIGH;

#ifdef NON_CP
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
#endif

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  #ifdef CIRCUIT_PLAYGROUND
  CircuitPlayground.begin();
  CircuitPlayground.strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  CircuitPlayground.strip.show();            // Turn OFF all pixels ASAP
  CircuitPlayground.strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.println("Circuit playground board used");
  #endif

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  #ifdef NON_CP
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.println("Code running for a non Circuit Playground board");
  #endif
  
  //Start-up colour sensor
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No Color Sensor found ... check your connections");
    //while (1); // halt!
  }

  pinMode(pushButton, INPUT);
  Keyboard.begin();

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

  int buttonState = digitalRead(pushButton);
  
  if (buttonState == HIGH) {
    Keyboard.print((int)r, HEX);
    delay(300);
    Keyboard.print((int)g, HEX);
    delay(300);
    Keyboard.print((int)b, HEX);
    Serial.println("button");
    Keyboard.println();
    delay(300);
  }

  Serial.print("HEX: \t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.print("\t \t RGB: \t");
  Serial.print((int)r );
  Serial.print(" ");
  Serial.print((int)g);
  Serial.print(" ");
  Serial.println((int)b );
  Serial.println();

  #ifdef NON_CP
  colorWipe(strip.Color(r, g, b), 50);
  #endif

  #ifdef CIRCUIT_PLAYGROUND
  colorWipe(CircuitPlayground.strip.Color(r, g, b), 50);
  #endif

  oled.clearDisplay();          // clear displa
  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(1, 1);        // position to display
  oled.println("Press button and hold to send HEX");
  
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(2, 30);        // position to display
  oled.println("HEX:");
  oled.setCursor(50, 30);        // position to display
  oled.println((int)r, HEX);
  oled.setCursor(74, 30);        // position to display
  oled.println((int)g, HEX);
  oled.setCursor(98, 30);        // position to display
  oled.println((int)b, HEX);     // text to display
  oled.display();                // show on OLED

  delay(2000);

}

void colorWipe(uint32_t color, int wait) {
  
    #ifdef CIRCUIT_PLAYGROUND
    for (int i = 0; i < CircuitPlayground.strip.numPixels(); i++) { // For each pixel in strip...
    CircuitPlayground.strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    CircuitPlayground.strip.show();                          //  Update strip to match
    #endif

    #ifdef NON_CP
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    #endif
    
    delay(wait);                           //  Pause for a moment
  }
}
