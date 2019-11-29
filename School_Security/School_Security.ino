#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <rdm6300.h>
#include <Wire.h>

#define RDM6300_RX_PIN 13 //D7 - on esp8266 force hardware uart!

#define READ_LED 16 //D0
#define SUCCESS_LED 15 //D8

#define D2 4
#define D1 5

/** WIFI Configuration **/
const char *ssid = "Hridoy";
const char *password = "9876543210";
const char *host = "192.168.0.100";

LiquidCrystal_I2C lcd(0x3F, 16, 2);
//Rdm6300 rdm6300;
 String card = "EE22A8";
 
void setup() {
  Serial.begin(9600);
  //Pinout Config
  pinMode(READ_LED, OUTPUT);
  digitalWrite(READ_LED, LOW);

  pinMode(SUCCESS_LED, OUTPUT);
  digitalWrite(SUCCESS_LED, LOW);

  //Activate RFID
  //rdm6300.begin(RDM6300_RX_PIN);

  //Activate WiFi
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("Connecting");
  //Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
Wire.begin(D2, D1);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print("School--Security");
  delay(900);
  lcd.clear();
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print("PLEASE TOUCH UR");

  lcd.setCursor(0, 1);
  lcd.print("   RFID CARD   ");

  for(int i = 0; i<5 ; i++){
  //if (rdm6300.update()) {
    //Serial.println(rdm6300.get_tag_id(), HEX);

    //digitalWrite(READ_LED, rdm6300.is_tag_near());
    //charToString(cards[i][], &rfid);
  
    HTTPClient http;
    String postData;

    //Post Data
    postData = "rfid=" + card;
    http.begin("http://192.168.0.100/sss/attendance_api.php");          //Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

    int httpCode = http.POST(postData);   //Send the request
    String payload = http.getString();    //Get the response payload

    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload

    http.end();  //Close connection
    delay(5000);
  }
}

void charToString(const char S[], String &D)
{
  byte at = 0;
  const char *p = S;
  D = "";
  while (*p++) {
    D.concat(S[at++]);
  }
}
