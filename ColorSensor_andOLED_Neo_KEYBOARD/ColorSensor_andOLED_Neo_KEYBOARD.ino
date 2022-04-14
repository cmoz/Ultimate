/* 
 *  Works on Flora and Circuit Playground boards. Will need to modify for the 
 *  NeoPixel strip is all, depending on the board.s
 *  
 *  OLED using I2C
 *  KEYBOARD USB to input the HEX code into where their curcor is
 *  Uses  button to press to copy the code to text file
 *  
 *  NEOs on PIN 10
 *  BUTTON on PIN 12 
 *  
 */


#include "Keyboard.h"
#include <Wire.h>                  //include Wire.h to be able to communicate through I2C on Arduino board
#include <Adafruit_CircuitPlayground.h>

#include "Adafruit_TCS34725.h"     //Colour sensor library
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
//#include "Adafruit_NeoPixel.h" 

//Create colour sensor object declaration, to see effects of different integration time and gain
//settings, check the datatsheet of the Adafruit TCS34725.
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define LED_PIN    10
#define LED_COUNT 25

int pushButton = 12;
int previousButtonState = HIGH;
//Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();

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

  CircuitPlayground.strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  CircuitPlayground.strip.show();            // Turn OFF all pixels ASAP
  CircuitPlayground.strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  pinMode(pushButton, INPUT);
  Keyboard.begin();3D8267
  3D8367
  3C8267
  
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

  colorWipe(CircuitPlayground.strip.Color(r, g, b), 50);

  oled.clearDisplay();          // clear displa

  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(1, 1);        // position to display
  oled.println("Press button and hold to send HEX");
  
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

  delay(2000);


}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < CircuitPlayground.strip.numPixels(); i++) { // For each pixel in strip...
    CircuitPlayground.strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    CircuitPlayground.strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
