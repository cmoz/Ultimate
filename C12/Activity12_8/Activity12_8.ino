#include <SPI.h>
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

boolean redTag = false;
boolean purpleTag = false;
boolean yellowTag = false;
boolean greenTag = false;
boolean blueTag = false;

int card1 = redTag;
int card2 = purpleTag;
int card3 = yellowTag;
int card4 = greenTag;
int card5 = blueTag;

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  Serial.setTimeout(20000); // to wait for up to 20s in "read" functions
  while (!Serial) { }

  // you must call this initialization function for the RFID reader!
  rfid.PCD_Init(); // MFRC522
  delay(4);

  strip.begin();
  strip.setBrightness(45);
  strip.show();
  rainbowEffect(1, 3);
  delay(300);
  rfid.PCD_DumpVersionToSerial();	// Show details of MFRC522 Card Reader
  Serial.println(F("Scan tag..."));
  strip.fill((0, 0, 0), 0);
  strip.show();
  strip.clear();
}

void loop() {

  while (getID())
  {
    Serial.println(tagID);
    if (tagID == redTagUID)
    {
      tagActions('1');
    }
    else if (tagID == purpleTagUID)
    {
      tagActions('2');
    }
    else if (tagID == yellowTagUID)
    {
      tagActions('3');
    }
    else if (tagID == greenTagUID)
    {
      tagActions('4');
    }
    else if (tagID == blueTagUID)
    {
      tagActions('5');
    }
    else
    {
      rainbowEffect(1, 2);
      Serial.println("tag not recognised");
    }
  }
  delay(1000);
}


void tagActions(char tag) {
  switch (tag) {
    case ('1'):
      Serial.println("red tag");
      redTag ^= true;
      if (redTag == true) {
        strip.setPixelColor(0, 255, 0, 10);
        strip.show();
        Serial.println("scan in R");
        delay(100);
      } else {
        Serial.println("scan out R");
        strip.setPixelColor(0, 0, 0, 0);
        strip.show();
      }
      break;
    case ('2'):
      Serial.println("purple tag");
      purpleTag ^= true;
      if (purpleTag == true) {
        strip.setPixelColor(1, 245, 0, 255);
        strip.show();
        Serial.println("scan in P");
        delay(100);
      } else {
        Serial.println("scan out P");
        strip.setPixelColor(1, 0, 0, 0);
        strip.show();
      }
      break;
    case ('3'):
      Serial.println("yellow tag");
      yellowTag ^= true;
      if (yellowTag == true) {
        strip.setPixelColor(2, 155, 125, 0);
        strip.show();
        Serial.println("scan in Y");
        delay(100);
      } else {
        Serial.println("scan out Y");
        strip.setPixelColor(2, 0, 0, 0);
        strip.show();
      }
      break;
    case ('4'):
      Serial.println("green tag");
      greenTag ^= true;
      if (greenTag == true) {
        strip.setPixelColor(3, 0, 255, 20);
        strip.show();
        Serial.println("scan in G");
        delay(100);
      } else {
        Serial.println("scan out G");
        strip.setPixelColor(3, 0, 0, 0);
        strip.show();
      }
      break;
    case ('5'):
      Serial.println("blue tag");
      blueTag ^= true;
      if (blueTag == true) {
        strip.setPixelColor(4, 0, 10, 255);
        strip.show();
        Serial.println("scan in B");
        delay(100);
      } else {
        Serial.println("scan out B");
        strip.setPixelColor(4, 0, 0, 0);
        strip.show();
      }
      break;
    default:
      Serial.print(" ");
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
