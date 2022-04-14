/* @cmoz
 *  
 * Activity 7.6: Adding an OLED for displaying information
 * 
 * This is an example how to use Touch Interrupts
 * The bigger the threshold, the more sensitive the touch
 * Testing 3 touch input pins 
 * 
 * Also the output will display on an OLED which touch was triggered
 * 
 */

#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


int threshold = 40;
bool touch1detected = false;
bool touch2detected = false;
bool touch3detected = false;

void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Interrupt Test");
  touchAttachInterrupt(T5, gotTouch1, threshold);
  touchAttachInterrupt(T3, gotTouch2, threshold);
  touchAttachInterrupt(T0, gotTouch3, threshold);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(3);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println("Hello  World!"); // text to display
  oled.display();               // show on OLED
}

void loop(){
  if(touch1detected){
    touch1detected = false;
    Serial.println("Touch 1 detected: GPIO 12");
    oled.clearDisplay();
    oled.setTextSize(3);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(0, 20);        // position to display
    oled.println("Touch 1");      // text to display
    oled.display();               // show on OLED
    delay(2000);
  }
  if(touch2detected){
    touch2detected = false;
    Serial.println("Touch 2 detected : GPIO 15");
    oled.clearDisplay();
    oled.setTextSize(3);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(0, 20);        // position to display
    oled.println("Touch 2");      // text to display
    oled.display();               // show on OLED
    delay(2000);
  }
  if(touch3detected){
    touch3detected = false;
    Serial.println("Touch 3 detected: GPIO 4");
    oled.clearDisplay();
    oled.setTextSize(1);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(0, 0);        // position to display
    oled.println("Touched");      // text to display
    oled.setTextSize(3);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(0, 20);        // position to display
    oled.println("Three");      // text to display
    oled.display();               // show on OLED
    delay(2000);
  }
}

void gotTouch1(){
 touch1detected = true;
}

void gotTouch2(){
 touch2detected = true;
}

void gotTouch3(){
 touch3detected = true;
}
