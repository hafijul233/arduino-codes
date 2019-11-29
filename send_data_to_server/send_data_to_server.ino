#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>

// defines pins numbers
#define trigPin  4 //D2
#define echoPin  5 //D1
#define tank_height 22 //in Centimeter

//Wifi Settings
const char *ssid = "Hridoy";
const char *password = "9876543210";
const char *host = "192.168.1.20";

//Server Setting
const char *serverUrl = "http://192.168.1.20/oil/entry_point.php";
String postStr = "";
String apiKey = "TW9oYW1tYWQgSGFmaWp1bCBJc2xhbQ";
//Status Flags
bool wifiStatus = false;

//variables
int i = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  lcd.init();
  lcd.backlight();

  //Welcome Note
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO   ");
  lcd.setCursor(0, 1);
  lcd.print("IoT Fuel Monitor");
  delay(700);
  lcd.clear();

  //Wifi connection
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  Serial.println("Connecting To Wifi ");
  do {
    if (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("WiFi Connection Failed.");
    } else {
      Serial.println("Wifi Connection Successful.");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());  //IP address assigned to your ESP
      wifiStatus = true;
      break;
    }
    i++;
  } while (i < 5);

  //Check got Any Connection with in 2.5 Sec.
  if (wifiStatus == false) {
    lcd.setCursor(0, 0);
    lcd.print("  WiFi Failed  ");
    lcd.setCursor(0, 1);
    lcd.print(" Disp: OFFLINE ");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connection");
    lcd.setCursor(0, 1);
    lcd.print(" Disp: ONLINE ");
  }
  lcd.clear();
}

void loop()
{
  float oilLevel = calculate_fuel();
  //LCD print
  lcd.setCursor(0, 0);
  lcd.print("OIL LEV. ");
  lcd.print(oilLevel);
  lcd.print(" %");

  lcd.setCursor(0, 1);
  if (oilLevel >= 0 && oilLevel <= 100) {
    if (oilLevel < 2) {
      lcd.print("Warn: EMPTY");
    } else if (oilLevel >= 2 && oilLevel < 25) {
      lcd.print("Warn: LOW LEVEL");
    } else if (oilLevel >= 25 && oilLevel < 75) {
      lcd.print("Warn: MEDIUM");
    } else if (oilLevel >= 75 && oilLevel <= 100) {
      lcd.print("Warn: FULL");
    }
  } else {
    oilLevel = 74369;
    lcd.print("Warn: INVALID");
  }
  sendDataToServer(oilLevel);
  delay(3000);
  lcd.clear();

}

float calculate_fuel()
{
  unsigned long duration;
  int distance;
  float percentage;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" CM");
  percentage = ((tank_height - distance) * 100.0) / tank_height;

  return percentage;
}


void sendDataToServer(float data)
{
  HTTPClient http;
  postStr = "ol=" + String(data, 2);
  postStr += "&api=" + apiKey;
  
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  //Web Feedback
  int httpCode = http.POST(postStr);
  String payload = http.getString();
  Serial.println(httpCode);
  Serial.println(payload);
  http.end();
}
