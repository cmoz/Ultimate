/* @cmoz
 *  
 * Activity 7.8: Connecting all the parts: ESP32 / OLED / vibration?
 * 
 * This is using Touch Interrupts
 * Making a call to a weather API for current weather data
 * 
 * Also the output will display on an OLED which touch was triggered
 * 
 */
 
#include <WiFi.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>

unsigned long entry;
String tempUnit = "";
String windUnit = "";

//HTTP call interval (milliseconds)
long getRate = 15000;     
long prevWeatherCall = getRate * -1;

//HTTP weather endpoint 
// CHANGE YOUR API KEY AT THE END OF EACH OF THESE LINES
String base_t = "http://api.openweathermap.org/data/2.5/weather?q=Toronto,ca&units=metric&appid=yourAPIkeyHERE";
String base_w = "http://api.openweathermap.org/data/2.5/weather?q=Winnipeg,ca&units=metric&appid=yourAPIkeyHERE";
String base_y = "http://api.openweathermap.org/data/2.5/weather?q=York,uk&units=metric&appid=yourAPIkeyHERE";

String units = "metric";

String weatherUrlT = base_t;
String weatherUrlW = base_w;
String weatherUrlY = base_y;

//Global variables to hold HTTP responses
String payload;
String parsedWeather[4] = {};

//Set memory space for the JSON, check https://arduinojson.org/v6/assistant/ 
StaticJsonDocument<1000> jsonWeather;

// CHANGE FOR YOUR SCREEN SIZE 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Blue LED pin is next to the USB port
#define BLUE_LED 2

int threshold = 40;
bool touch1detected = false;
bool touch2detected = false;
bool touch3detected = false;

// CHANGE TO YOUR SSID AND PASSWORD FOR YOUR NETWORK 
const char* ssid = "ssid";
const char* password =  "password";


void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  delay(1000); // time to bring up serial monitor
  Serial.println("ESP32 Touch Interrupt, OLED, and weather API Test");
  touchAttachInterrupt(T5, gotTouch1, threshold);
  touchAttachInterrupt(T3, gotTouch2, threshold);
  touchAttachInterrupt(T0, gotTouch3, threshold);

  //The red LED next to the USB port will flash during HTTP call
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(BLUE_LED, LOW);

// ======== set up OLED ===============
  // initialize OLED display with address 0x3C for 128x64
 if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 0x3D allocation failed"));
    for(;;);
  }
  delay(500);

  SPI.begin(); // Init SPI bus
  chooseUnits();
  wifiStart();
  oled.clearDisplay();

  oledStart();
}

void loop() {

  if(touch1detected){
    oled.clearDisplay();
    touch1detected = false;
    Serial.println("Touch 1 detected: GPIO 12 TO");
    displayMessage("How's Toronto?");
    
     if((millis() - prevWeatherCall) > getRate){
      updateWeather(weatherUrlT);
      prevWeatherCall = millis();
      delay(100);
      oledDisplay(parsedWeather);
      delay(getRate);
      oledStart(); 
      }
      
  }
  
  if(touch2detected){
    oled.clearDisplay();
    touch2detected = false;
    Serial.println("Touch 2 detected : GPIO 15 WPG");
    displayMessage("How's Winnipeg?");
      
      if((millis() - prevWeatherCall) > getRate){
      updateWeather(weatherUrlW);
      prevWeatherCall = millis();
      delay(100);
      oledDisplay(parsedWeather);
      delay(getRate);
      oledStart(); 
      }
  }
  
  if(touch3detected){
    oled.clearDisplay();
    touch3detected = false;
    Serial.println("Touch 3 detected: GPIO 4 YK");
    displayMessage("How's York?");

      if((millis() - prevWeatherCall) > getRate){
      updateWeather(weatherUrlY);
      prevWeatherCall = millis();
      delay(100);
      oledDisplay(parsedWeather);
      delay(getRate);
      oledStart(); 
      }
  }

}

// ====================================================================================================
// ====================================== OTHER FUNCTIONS =============================================
// ====================================================================================================
void gotTouch1(){
 touch1detected = true;
}

void gotTouch2(){
 touch2detected = true;
}

void gotTouch3(){
 touch3detected = true;
}

void displayMessage(String message){
    oled.clearDisplay();
    oled.invertDisplay(false);
    oled.setTextSize(1);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(0, 0);        // position to display
    oled.println(message);      // text to display
    oled.setCursor(5, 20);        // position to display
    oled.println("please");      // text to display
    oled.setCursor(40, 40);        // position to display
    oled.println("wait...");      // text to display
    oled.display();               // show on OLED
    delay(2000);
    oled.clearDisplay();
}

//Call weather API, parse data, send to OLED display
void updateWeather(String location){
  payload = httpGet(location);
    if(payload != "HTTP Error"){
      DeserializationError error = deserializeJson(jsonWeather, payload);
    if(error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
    parsedWeather[0] = jsonWeather["name"].as<String>();
    parsedWeather[1] = jsonWeather["weather"][0]["description"].as<String>();
    parsedWeather[2] = "Temp: " + jsonWeather["main"]["temp"].as<String>() + " " + tempUnit;
    parsedWeather[3] = "Wind: " + jsonWeather["wind"]["speed"].as<String>() + " " + windUnit;
  }
  else parsedWeather[0] = payload;
  oledDisplay(parsedWeather);
}

//Make HTTP Get Calll
String httpGet(String url){
  String payload;
  HTTPClient http;
  http.begin(url);
  digitalWrite(BLUE_LED, HIGH);
  int httpCode = http.GET();
  digitalWrite(BLUE_LED, LOW);
  
  if(httpCode == 200){
    payload = http.getString();
    Serial.println("HTTP Response code: " + httpCode);
  }
  else{
    Serial.println("HTTP Error Code: " + httpCode);
    payload = "HTTP Error";
  }
  http.end();
  return payload;
}

void oledStart(){
  oled.invertDisplay(false);
  oled.clearDisplay();
  delay(500);
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0); 
    oled.write(0x03); // character see https://en.wikipedia.org/wiki/Code_page_437
  oled.println(" How's the");
  oled.setTextSize(2);
  oled.setCursor(0, 20);  
  oled.println("weather?");
  oled.display();
  delay(2000);
}

//Display 4 lines of recieved data on the OLED 
void oledDisplay(String parsedJson[4]){
  oled.clearDisplay();
  oled.invertDisplay(true);
  oled.setTextSize(1);
  oled.setCursor(8,6);
  for(int i = 0; i < 4; i++){
    oled.println(parsedJson[i]);
    oled.setTextSize(1);
    oled.setCursor(8,(20+(i * 14)));
    oled.display();
  }
}

//Establish WiFi Connection
void wifiStart(){
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.print("\nConnected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


//Set displayed weather units based on "units" variable
void chooseUnits(){
  String tempUnit;
  
  if(units == "metric"){
    tempUnit = "C";
    windUnit = "km/h";
  }
  if(units == "imperial"){
    tempUnit = "F";
    windUnit = "mph";
  }
}
