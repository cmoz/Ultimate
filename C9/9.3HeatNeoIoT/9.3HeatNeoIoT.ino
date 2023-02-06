// Adafruit IO RGB LED Output Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016-2017 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Amended for our purpose *******************************/
// Using a QT Py ESP32 (S2 or C3) 
// Add to the circuit, neopixels on pin A2, Heat pad with diode, transistor, resistor 
// and connected to pin A3 on the board (GPIO 8 in the code)
// Connect to io service, add a color picker, and a slide switch toggle 

/************************ Code *******************************/


#include "Adafruit_NeoPixel.h"

#define PIXEL_PIN     A2
#define PIXEL_COUNT   8
#define PIXEL_TYPE    NEO_GRB + NEO_KHZ800

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

// set up the 'color' feed
AdafruitIO_Feed *color = io.feed("color");
AdafruitIO_Feed *button = io.feed("button");

int heatPin = 8;

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
 // while(! Serial);

  pinMode(heatPin, OUTPUT);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'color' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  color->onMessage(handleMessage);
  button->onMessage(handleHeatMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  color->get();
  button->get();

  // neopixel init
  pixels.begin();
  pixels.setBrightness(64);
  pixels.show();

  digitalWrite(heatPin, LOW);
  Serial.println("Heat off in setup");
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}

// this function is called whenever a 'color' message
// is received from Adafruit IO. it was attached to
// the color feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  // print RGB values and hex value
  Serial.println("Received HEX: ");
  Serial.println(data->value());

  long color = data->toNeoPixel();

  for(int i=0; i<PIXEL_COUNT; ++i) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}

void handleHeatMessage(AdafruitIO_Data *data) {
 
  Serial.println(data->value());
   
  bool button = data->value();

  if ((button) == 1) {
    digitalWrite(heatPin, HIGH);
    Serial.println("Hugs on");
  } else {
    digitalWrite(heatPin, LOW);
    Serial.println("Hugs off");
  }
  delay(100);
}
  
  

/*
  switch (button) {
    case 0:    // your hand is on the sensor
      digitalWrite(heatPin, LOW);
      Serial.println("Hugs off");
      break;
    case 1:    // your hand is close to the sensor
      digitalWrite(heatPin, HIGH);
      Serial.println("Hugs on");
      break;
  }
  delay(100);        // delay in between reads for stability
}

*/

  /*
  if (button == 1) {
    digitalWrite(heatPin, HIGH);
    Serial.println("Heat on");
  }

  else if (button == 0) {
    digitalWrite(heatPin, LOW);
    Serial.println("Heat off");
  }
  */
