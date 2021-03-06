#include <SPI.h>
#include <FlashStorage.h>
#include <MFRC522.h>
#include <Adafruit_NeoPixel.h>

#define SS_PIN 4
#define RST_PIN 3

MFRC522 rfid(SS_PIN, RST_PIN);

int neoPin = 1;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, neoPin, NEO_GRB + NEO_KHZ800);

byte readCard[4];
String redTagUID = "7A6CA21A";  // REPLACE this Tag ID with your Tag ID!!!
String purpleTagUID = "8C4CFF4";
String yellowTagUID = "B6E0972B";
String greenTagUID = "DBC24335";
String blueTagUID = "399DA1A3";
String tagID = "";

bool redTag;
bool purpleTag;
bool yellowTag;
bool greenTag;
bool blueTag;

FlashStorage(my_flash_storeR, bool);
FlashStorage(my_flash_storeP, bool);
FlashStorage(my_flash_storeY, bool);
FlashStorage(my_flash_storeG, bool);
FlashStorage(my_flash_storeB, bool);

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  Serial.setTimeout(20000); // to wait for up to 20s in "read" functions

  // you must call this initialization function for the RFID reader!
  rfid.PCD_Init(); // MFRC522
  delay(4);

  strip.begin();
  strip.setBrightness(255);
  rainbowEffect(1, 3);
  strip.show();
  delay(300);
  rfid.PCD_DumpVersionToSerial();	// Show details of MFRC522 Card Reader
  Serial.println(F("Scan tag..."));
  strip.fill((0, 0, 0), 0);
  strip.show();
  //strip.clear();

  redTag = my_flash_storeR.read();
  purpleTag = my_flash_storeP.read();
  yellowTag = my_flash_storeY.read();
  greenTag = my_flash_storeG.read();
  blueTag = my_flash_storeB.read();

  Serial.println(redTag);
  Serial.println(purpleTag);
  Serial.println(yellowTag);
  Serial.println(blueTag);
  Serial.println(greenTag);
  
  setNeoColor();
}

void loop() {

  while (getID())
  {
    Serial.println(tagID);
    rainbowEffect(1, 1);
    if (tagID == redTagUID)
    {
      tagActions('0');
    }
    else if (tagID == yellowTagUID)
    {
      tagActions('1');
    }
    else if (tagID == greenTagUID)
    {
      tagActions('2');
    }
    else if (tagID == blueTagUID)
    {
      tagActions('3');
    }
    else if (tagID == purpleTagUID)
    {
      tagActions('4');
    }
    else
    {
      rainbowEffect(1, 1);
      Serial.println("tag not recognised");
    }
    setNeoColor();
  }
}

void tagActions(char tag) {
  switch (tag) {
    case ('0'):
      Serial.println("red tag");
      redTag ^= true;
      my_flash_storeR.write(redTag);
      Serial.println(redTag);
      break;
    case ('1'):
      Serial.println("yellow tag");
      yellowTag ^= true;
      my_flash_storeY.write(yellowTag);
      Serial.println(yellowTag);
      break;
    case ('2'):
      Serial.println("green tag");
      greenTag ^= true;
      my_flash_storeG.write(greenTag);
      break;
    case ('3'):
      Serial.println("blue tag");
      blueTag ^= true;
      my_flash_storeB.write(blueTag);
      break;
    case ('4'):
      Serial.println("purple tag");
      purpleTag ^= true;
      my_flash_storeP.write(purpleTag);
      break;
    default:
      Serial.print(" ");
  }
}

void setNeoColor() {

  if (redTag == true) {
    Serial.println("set red Neo Color on");
    strip.setPixelColor(0, 255, 0, 0);
    strip.show();
    delay(100);
  } else if (redTag == false) {
    strip.setPixelColor(0, 0, 0, 0);
    strip.show();
  }

  if (yellowTag == true) {
    Serial.println("set yellow Neo Color on");
    strip.setPixelColor(1, 155, 115, 0);
    strip.show();
    delay(100);
  } else if (yellowTag == false) {
    strip.setPixelColor(1, 0, 0, 0);
    strip.show();
  }

  if (greenTag == true) {
    Serial.println("set green Neo Color on");
    strip.setPixelColor(2, 0, 150, 0);
    strip.show();
    delay(100);
  } else  if (greenTag == false) {
    strip.setPixelColor(2, 0, 0, 0);
    strip.show();
  }

  if (blueTag == true) {
    Serial.println("set blue Neo Color on");
    strip.setPixelColor(3, 0, 0, 255);
    strip.show();
    delay(100);
  } else if (blueTag == false) {
    strip.setPixelColor(3, 0, 0, 0);
    strip.show();
  }

  if (purpleTag == true) {
    Serial.println("set purple Neo Color on");
    strip.setPixelColor(4, 255, 0, 255);
    strip.show();
    delay(100);
  } else if (purpleTag == false) {
    strip.setPixelColor(4, 0, 0, 0);
    strip.show();
  }

  delay(15);
  Serial.println(redTag);
  Serial.println(yellowTag);
  Serial.println(greenTag);
  Serial.println(blueTag);
  Serial.println(purpleTag);

  checkAllOn();
}


void checkAllOn() {
  if ((redTag == true) && (purpleTag == true) && (
        yellowTag == true) && (greenTag == true) && (blueTag == true)) {
    rainbowEffect(3, 5);
  }
  if ((redTag == false) && (purpleTag == false) && (
        yellowTag == false) && (greenTag == false) && (blueTag == false)) {
    theaterChase(strip.Color(  0,   110, 127), 100);
    strip.fill((150,150,255),0);
    strip.show();
  }
}

void rainbowEffect(uint8_t wait, int cycles) {
  uint16_t x, y;
  strip.setBrightness(45);
  for (y = 0; y < 256 * cycles; y++) { // 5 cycles of all colors on wheel
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

boolean getID()
{
  // Getting ready for Reading PICCs
  if ( ! rfid.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return false;
  }
  if ( ! rfid.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
    //readCard[i] = mfrc522.uid.uidByte[i];
    tagID.concat(String(rfid.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  rfid.PICC_HaltA(); // Stop reading
  return true;
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) { // Repeat 10 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
    strip.fill((50, 50, 50), 0);
    strip.show();
  }

}
