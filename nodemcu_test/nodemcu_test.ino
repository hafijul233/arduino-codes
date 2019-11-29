#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>

// defines pins numbers
//sensor
#define tank_height 22 //in Centimeter
#define trigPin  5 //D1
#define echoPin  4 //D2
//display
#define lcda  0 //D3 //SDA
#define lcdl  2 //D4 //SCL

//Wifi Settings
const char *ssid = "Hridoy";
const char *password = "9876543210";
const char *host = "192.168.1.23";

//Server Setting
const char *serverUrl = "http://oil.csl-erp.com/entry_point.php";
String postStr = "";
String apiKey = "TW9oYW1tYWQgSGFmaWp1bCBJc2xhbQ";
bool wifiStatus = false;
//variables
int i = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);
  lcd.begin(lcda, lcdl);
  lcd.backlight();
  //setting Pinout
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO   ");
  Serial.println("WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print("IoT Oil Monitor ");
  Serial.println("IoT Oil Monitor");
  //Wifi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  delay(900);
  lcd.clear();
}

void loop() {
  float oilLevel = calculate_fuel();
  lcd.setCursor(0, 0);
  if (oilLevel >= 0 && oilLevel < 2) {
    lcd.print("Status: EMPTY");
  } else if (oilLevel >= 2 && oilLevel < 25) {
    lcd.print("Status: LOW");
  } else if (oilLevel >= 25 && oilLevel < 75) {
    lcd.print("Status: MEDIUM");
  } else if (oilLevel >= 75 && oilLevel <= 100) {
    lcd.print("Status: FULL");
  } else {
    oilLevel = 74369;
    lcd.print("Status: INVALID");
  }
  //Oil Level
  lcd.setCursor(0, 1);
  lcd.print("OIL LEV.");
  lcd.print(oilLevel);
  lcd.print(" %");

  if(i == 3) {
  HTTPClient http;
    postStr = "ol=" + String(oilLevel, 2);
    postStr += "&api=" + apiKey;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    //Web Feedback
    int httpCode = http.POST(postStr);
    //String payload = http.getString();
    Serial.println(httpCode);
    //Serial.println(payload);
    http.end();
    i = 0;
  }
  i++;
  delay(3000);
  lcd.clear();
}

float calculate_fuel() {
  long duration, distance, filled;
  float percentage;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //Calculate Distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" CM");
  filled = tank_height - distance;
  percentage = (filled * 100.0) / tank_height;
  return percentage;
}
